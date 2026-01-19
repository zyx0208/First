// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Blueprint/UserWidget.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponPosition = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponPosition"));
	WeaponPosition->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	//초기 설정
	MoveSpeed = GetCharacterMovement()->MaxWalkSpeed;
	IsRun = false;
	IsWalk = false;
	IsOptionUIMode = false;
	IsInventoryUIMode = false;
	IsSkillUIMode = false;
	ToggleCrosshair();
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//움직임 판단
	IsWalk = !FMath::IsNearlyZero(GetInputAxisValue("MoveForward")) || !FMath::IsNearlyZero(GetInputAxisValue("MoveRight"));
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//이동
	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);

	//달리기
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AMyCharacter::StartRun);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AMyCharacter::StopRun);

	//마우스 회전
	PlayerInputComponent->BindAxis("Turn", this, &AMyCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AMyCharacter::LookUp);

	//옵션
	PlayerInputComponent->BindAction("Option", IE_Pressed, this, &AMyCharacter::ToggleOption).bExecuteWhenPaused = true;

	//인벤토리
	PlayerInputComponent->BindAction("Inventory", IE_Pressed, this, &AMyCharacter::ToggleInventory);

	//스킬창
	PlayerInputComponent->BindAction("Skill", IE_Pressed, this, &AMyCharacter::ToggleSkill);

	//점프
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::Jump);
}

void AMyCharacter::MoveForward(float value)
{
	if ((Controller) && (value != 0.0f))
	{
		//현재 시점 불러오기
		FRotator PlayerRotator(0, Controller->GetControlRotation().Yaw, 0);
		//백터 정규화
		FVector Direction = FRotationMatrix(PlayerRotator).GetUnitAxis(EAxis::X);

		AddMovementInput(Direction, value);
	}
}

void AMyCharacter::MoveRight(float value)
{
	if ((Controller) && (value != 0.0f))
	{
		//현재 시점 불러오기
		FRotator PlayerRotator(0, Controller->GetControlRotation().Yaw, 0);
		//백터 정규화
		FVector Direction = FRotationMatrix(PlayerRotator).GetUnitAxis(EAxis::Y);

		AddMovementInput(Direction, value);
	}
}

void AMyCharacter::StartRun()
{
	IsRun = true;
	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed * 2.0f;
}

void AMyCharacter::StopRun()
{
	IsRun = false;
	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
}

void AMyCharacter::Turn(float value)
{
	if (!(IsOptionUIMode || IsInventoryUIMode || IsSkillUIMode))
	{
		AddControllerYawInput(value);
	}
}

void AMyCharacter::LookUp(float value)
{
	if (!(IsOptionUIMode || IsInventoryUIMode || IsSkillUIMode))
	{
		AddControllerPitchInput(value);
	}
}

void AMyCharacter::ToggleOption()
{
	//UI미지정
	if (!OptionUIClass)
	{
		UE_LOG(LogTemp, Log, TEXT("Option UI is not existed."));
		return;
	}

	//옵션 버튼을 연타하면 모든 UI가 제거되도록
	if (CheckingUI())
	{
		ShutdownAllUI();
		return;
	}

	//최초 생성
	if (!OptionUI)
	{
		OptionUI = CreateWidget<UUserWidget>(GetWorld(), OptionUIClass);
	}

	if (OptionUI)
	{
		if (OptionUI->IsInViewport()) //이미 UI가 존재하는 경우
		{
			UE_LOG(LogTemp, Log, TEXT("Option UI Close."));
			//게임 진행 설정
			OptionUI->RemoveFromParent();
			OptionUI = nullptr;

			IsOptionUIMode = false;

			APlayerController* PController = Cast<APlayerController>(GetController());
			if (PController)
			{
				PController->SetPause(false);
				PController->bShowMouseCursor = false;
				PController->SetInputMode(FInputModeGameOnly());
			}
		}
		else //UI가 꺼져있는 경우
		{
			UE_LOG(LogTemp, Log, TEXT("Option UI Open."));
			//UI 진행 설정
			OptionUI->AddToViewport();

			IsOptionUIMode = true;

			APlayerController* PController = Cast<APlayerController>(GetController());
			if (PController)
			{
				PController->SetPause(true);
				PController->bShowMouseCursor = true;
				PController->SetInputMode(FInputModeGameAndUI());
			}
		}
	}
}

void AMyCharacter::ToggleInventory()
{
	//UI미지정
	if (!InventoryUIClass)
	{
		UE_LOG(LogTemp, Log, TEXT("Inventory UI is not existed."));
		return;
	}

	//최초 생성
	if (!InventoryUI)
	{
		InventoryUI = CreateWidget<UUserWidget>(GetWorld(), InventoryUIClass);
	}

	if (InventoryUI)
	{
		if (InventoryUI->IsInViewport()) //이미 UI가 존재하는 경우
		{
			UE_LOG(LogTemp, Log, TEXT("Inventory UI Close."));
			//게임 진행 설정
			InventoryUI->RemoveFromParent();
			InventoryUI = nullptr;

			IsInventoryUIMode = false;

			APlayerController* PController = Cast<APlayerController>(GetController());
			if (PController)
			{
				PController->bShowMouseCursor = false;
				PController->SetInputMode(FInputModeGameOnly());
			}
		}
		else //UI가 꺼져있는 경우
		{
			//다른 UI 제거
			if (CheckingUI())
			{
				ShutdownAllUI();
			}

			UE_LOG(LogTemp, Log, TEXT("Inventory UI Open."));
			//UI 진행 설정
			InventoryUI->AddToViewport();

			IsInventoryUIMode = true;

			APlayerController* PController = Cast<APlayerController>(GetController());
			if (PController)
			{
				PController->bShowMouseCursor = true;
				PController->SetInputMode(FInputModeGameAndUI());
			}
		}
	}
}

void AMyCharacter::ToggleSkill()
{
	//UI미지정
	if (!SkillUIClass)
	{
		UE_LOG(LogTemp, Log, TEXT("Skill UI is not existed."));
		return;
	}

	//최초 생성
	if (!SkillUI)
	{
		SkillUI = CreateWidget<UUserWidget>(GetWorld(), SkillUIClass);
	}

	if (SkillUI)
	{
		if (SkillUI->IsInViewport()) //이미 UI가 존재하는 경우
		{
			UE_LOG(LogTemp, Log, TEXT("Skill UI Close."));
			//게임 진행 설정
			SkillUI->RemoveFromParent();
			SkillUI = nullptr;

			IsSkillUIMode = false;

			APlayerController* PController = Cast<APlayerController>(GetController());
			if (PController)
			{
				PController->bShowMouseCursor = false;
				PController->SetInputMode(FInputModeGameOnly());
			}
		}
		else //UI가 꺼져있는 경우
		{
			//다른 UI 제거
			if (CheckingUI())
			{
				ShutdownAllUI();
			}

			UE_LOG(LogTemp, Log, TEXT("Skill UI Open."));
			//UI 진행 설정
			SkillUI->AddToViewport();

			IsSkillUIMode = true;

			APlayerController* PController = Cast<APlayerController>(GetController());
			if (PController)
			{
				PController->bShowMouseCursor = true;
				PController->SetInputMode(FInputModeGameAndUI());
			}
		}
	}
}

bool AMyCharacter::CheckingUI()
{
	return (IsInventoryUIMode || IsSkillUIMode);
}

void AMyCharacter::ShutdownAllUI()
{
	if (IsInventoryUIMode) ToggleInventory();
	if (IsSkillUIMode) ToggleSkill();
}

void AMyCharacter::StartJump()
{
	Jump();
}

void AMyCharacter::ToggleCrosshair()
{
	if (!CrosshairUIClass)
	{
		UE_LOG(LogTemp, Log, TEXT("Crosshair UI is not existed."));
		return;
	}

	if (!CrosshairUI)
	{
		CrosshairUI = CreateWidget<UUserWidget>(GetWorld(), CrosshairUIClass);
	}

	if (CrosshairUI)
	{
		if (CrosshairUI->IsInViewport()) //이미 크로스헤어가 존재하는 경우
		{
			UE_LOG(LogTemp, Log, TEXT("Off Crosshair."));
			CrosshairUI->RemoveFromParent();
			CrosshairUI = nullptr;
		}
		else //크로스헤어가 없는 경우
		{
			UE_LOG(LogTemp, Log, TEXT("On Crosshair."));
			CrosshairUI->AddToViewport();
		}
	}
}

void AMyCharacter::WeaponAttach(TSubclassOf<AWeaponBase> TargetWeapon)
{
	//무기가 입력되지 않으면 장착 취소
	if (!TargetWeapon) return;

	//무기가 이미 있으면 해제
	if (Weapon)
	{
		WeaponDetach();
	}

	//무기 장착
	UE_LOG(LogTemp, Log, TEXT("Weapon Attached."));
	Weapon = GetWorld()->SpawnActor<AWeaponBase>(TargetWeapon);
	Weapon->AttachToComponent(WeaponPosition, FAttachmentTransformRules::KeepRelativeTransform);
}

void AMyCharacter::WeaponDetach()
{
	//무기가 이미 없으면 그냥 종료
	if (!Weapon) return;

	UE_LOG(LogTemp, Log, TEXT("Weapon Detached."));
	Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	Weapon->Destroy();
	Weapon = nullptr;
}