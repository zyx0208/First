// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Blueprint/UserWidget.h"
#include "IngameUI.h"

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

	DefaultStatSeting();
	ApplyStat();
	HealHP(MaxHP);

	//초기 설정
	MoveSpeed = GetCharacterMovement()->MaxWalkSpeed;
	IsRun = false;
	IsWalk = false;
	IsOptionUIMode = false;
	IsInventoryUIMode = false;
	IsSkillUIMode = false;
	IsSkill1Cooltime = false;
	IsSkill2Cooltime = false;
	IsSkill3Cooltime = false;
	IsSkill4Cooltime = false;
	if (!EXP) EXP = 0;
	ToggleCrosshair();

	//임시 스킬 설정
	SKillIdx[0] = 0;
	SKillIdx[1] = 1;
	SKillIdx[2] = 2;
	SKillIdx[3] = 3;

	//인게임 UI 설정
	if (IngameUIClass)
	{
		IngameUI = CreateWidget<UIngameUI>(GetWorld(), IngameUIClass);
		IngameUI->AddToViewport();

		//스킬 쿨타임 UI 초기화
		IngameUI->Skill1CooltimeUI(0.0f, 1.0f);
		IngameUI->Skill2CooltimeUI(0.0f, 10.0f);
		IngameUI->Skill3CooltimeUI(0.0f, 10.0f);
		IngameUI->Skill4CooltimeUI(0.0f, 10.0f);
	}
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//움직임 판단
	IsWalk = !FMath::IsNearlyZero(GetInputAxisValue("MoveForward")) || !FMath::IsNearlyZero(GetInputAxisValue("MoveRight"));

	//스킬 쿨타임 판단
	if (IsSkill1Cooltime)
	{
		IngameUI->Skill1CooltimeUI(GetWorld()->GetTimerManager().GetTimerRemaining(Skill1TimerHandle), Skill1Cooltime);
	}
	if (IsSkill2Cooltime)
	{
		IngameUI->Skill2CooltimeUI(GetWorld()->GetTimerManager().GetTimerRemaining(Skill2TimerHandle), Skill2Cooltime);
	}
	if (IsSkill3Cooltime)
	{
		IngameUI->Skill3CooltimeUI(GetWorld()->GetTimerManager().GetTimerRemaining(Skill3TimerHandle), Skill3Cooltime);
	}
	if (IsSkill4Cooltime)
	{
		IngameUI->Skill4CooltimeUI(GetWorld()->GetTimerManager().GetTimerRemaining(Skill4TimerHandle), Skill4Cooltime);
	}
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

	//스킬
	PlayerInputComponent->BindAction("Skill_1", IE_Pressed, this, &AMyCharacter::UseSkill1);
	PlayerInputComponent->BindAction("Skill_2", IE_Pressed, this, &AMyCharacter::UseSkill2);
	PlayerInputComponent->BindAction("Skill_3", IE_Pressed, this, &AMyCharacter::UseSkill3);
	PlayerInputComponent->BindAction("Skill_4", IE_Pressed, this, &AMyCharacter::UseSkill4);

	//마우스모드
	PlayerInputComponent->BindAction("MouseMode", IE_Pressed, this, &AMyCharacter::ToggleMouseModeOn);
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

void AMyCharacter::UseSkill1()
{
	if(Weapon && !Weapon->IsAttacking) 
	{
		if (!IsSkill1Cooltime)
		{
			IsSkill1Cooltime = true;
			Weapon->UseSkill(SKillIdx[0]);
			Skill1Cooltime = 1.0f * (1.0f - ((float)Cooldown / 100.0f));
			GetWorld()->GetTimerManager().SetTimer(Skill1TimerHandle, this, &AMyCharacter::Skill1TimerEnd, Skill1Cooltime, false);
		}
	}
}

void AMyCharacter::UseSkill2()
{
	if (Weapon && !Weapon->IsAttacking)
	{
		if (!IsSkill2Cooltime)
		{
			IsSkill2Cooltime = true;
			Weapon->UseSkill(SKillIdx[1]);
			Skill2Cooltime = 10.0f * (1.0f - ((float)Cooldown / 100.0f));
			GetWorld()->GetTimerManager().SetTimer(Skill2TimerHandle, this, &AMyCharacter::Skill2TimerEnd, Skill2Cooltime, false);
		}
	}
}

void AMyCharacter::UseSkill3()
{
	if (Weapon && !Weapon->IsAttacking)
	{
		if (!IsSkill3Cooltime)
		{
			IsSkill3Cooltime = true;
			Weapon->UseSkill(SKillIdx[2]);
			Skill3Cooltime = 10.0f * (1.0f - ((float)Cooldown / 100.0f));
			GetWorld()->GetTimerManager().SetTimer(Skill3TimerHandle, this, &AMyCharacter::Skill3TimerEnd, Skill3Cooltime, false);
		}
	}
}

void AMyCharacter::UseSkill4()
{
	if (Weapon && !Weapon->IsAttacking)
	{
		if (!IsSkill4Cooltime)
		{
			IsSkill4Cooltime = true;
			Weapon->UseSkill(SKillIdx[3]);
			Skill4Cooltime = 10.0f * (1.0f - ((float)Cooldown / 100.0f));
			GetWorld()->GetTimerManager().SetTimer(Skill4TimerHandle, this, &AMyCharacter::Skill4TimerEnd, Skill4Cooltime, false);
		}
	}
}

void AMyCharacter::Skill1TimerEnd()
{
	IsSkill1Cooltime = false;
}

void AMyCharacter::Skill2TimerEnd()
{
	IsSkill2Cooltime = false;
}

void AMyCharacter::Skill3TimerEnd()
{
	IsSkill3Cooltime = false;
}

void AMyCharacter::Skill4TimerEnd()
{
	IsSkill4Cooltime = false;
}

void AMyCharacter::HealHP(int value)
{
	if (CurrentHP + value >= MaxHP)
	{
		CurrentHP = MaxHP;
		if (IngameUI)
		{
			IngameUI->ChangeHPBar();
		}
	}
	else
	{
		CurrentHP += value;
		if (IngameUI)
		{
			IngameUI->ChangeHPBar();
		}
	}
}

void AMyCharacter::AddEXP(int value)
{
	EXP += value;
	if (IngameUI)
	{
		IngameUI->ChangeEXPBar();
	}
	//중복 레벨업을 위한 반복문
	while (EXP >= MaxEXP)
	{
		EXP -= MaxEXP;
		MaxEXPSeting();
		LevelUp();
	}
}

void AMyCharacter::LevelUp()
{
	//레벨 증가
	Level++;

	//최종 스텟 계산
	ApplyStat();

	//풀피로 회복
	HealHP(MaxHP);
}

void AMyCharacter::Attacked(int value)
{
	//방어력을 추가할 의향이 있으면 해당 위치에 계산식 추가
	if (value >= CurrentHP)
	{
		CurrentHP = 0;
	}
	else
	{
		CurrentHP -= value;
	}
	
	//체력 UI 갱신
	if (IngameUI)
	{
		IngameUI->ChangeHPBar();
	}
	if (CurrentHP <= 0)
	{
		Death();
	}
}

void AMyCharacter::Death()
{
	UE_LOG(LogTemp, Log, TEXT("Player Death!"));
}

void AMyCharacter::ToggleMouseModeOn()
{
	APlayerController* PController = Cast<APlayerController>(GetController());
	if (PController && !CheckingUI() && !IsOptionUIMode)
	{
		if (PController->bShowMouseCursor)
		{
			//마우스 모드 끄기
			PController->bShowMouseCursor = false;
			PController->SetInputMode(FInputModeGameOnly());
		}
		else
		{
			//마우스 모드 켜기
			SetCenterMouse();
			PController->bShowMouseCursor = true;
			PController->SetInputMode(FInputModeGameAndUI());
		}
	}
}

void AMyCharacter::SetCenterMouse()
{
	APlayerController* PController = Cast<APlayerController>(GetController());
	int32 X, Y;
	PController->GetViewportSize(X, Y);
	PController->SetMouseLocation(X / 2, Y / 2);
}

float AMyCharacter::HPPercent()
{
	if ((CurrentHP <= 0) || MaxHP <= 0) return 0.0f;
	else return (float)CurrentHP / (float)MaxHP;
}

float AMyCharacter::EXPPercent()
{
	if ((EXP <= 0) || MaxEXP <= 0) return 0.0f;
	else return (float)EXP / (float)MaxEXP;
}

void AMyCharacter::ApplyStat()
{
	//체력, 공격력 설정(0~...)
	MaxHP = DefaultMaxHP + Level;
	AttackDamage = DefaultAttackDamage + Level;
	
	//쿨타임감소 설정(0~50)
	int temp = DefaultCooldown + Level;
	if (temp >= 50)
	{
		Cooldown = 50;
	}
	else if (temp <= 0)
	{
		Cooldown = 0;
	}
	else
	{
		Cooldown = temp;
	}
	
	//최대 경험치량 갱신
	MaxEXPSeting();

	//체력 UI 갱신
	if (IngameUI)
	{
		IngameUI->ChangeHPBar();
		IngameUI->ChangeEXPBar();
	}
}

void AMyCharacter::ResetLevel()
{
	Level = 1;
	EXP = 0;
	MaxEXPSeting();
	ApplyStat();
	HealHP(MaxHP);
}

void AMyCharacter::MaxEXPSeting()
{
	//다음 레벨까지 필요한 경험치량 공식
	MaxEXP = Level + 9;
}

void AMyCharacter::DefaultStatSeting()
{
	//레벨은 1부터 시작하므로, 원하는 시작값에 -1을 적용해서 계산
	DefaultMaxHP = 9;
	DefaultAttackDamage = 9;
	DefaultCooldown = -1;
}

