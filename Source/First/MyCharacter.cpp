// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Blueprint/UserWidget.h"
#include "IngameUI.h"
#include "InventoryUI.h"
#include "InventoryComponent.h"
#include "NPC.h"
#include "SelectShop.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//무기 Transform 정보를 저장하는 씬 컴포넌트 생성 및 루트에 자식으로 배치
	WeaponPosition = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponPosition"));
	WeaponPosition->SetupAttachment(RootComponent);

	//인벤토리 컴포넌트 클래스 생성
	CharacterInventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("CInventory"));
	CharacterInventory->PC = this;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	DefaultStatSeting();
	ApplyStat();
	HealHP(MaxHP);

	//초기 설정
	PController = Cast<APlayerController>(GetController());
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
	IsSlot1Cooltime = false;
	IsSlot2Cooltime = false;
	IsSlot3Cooltime = false;
	IsSlot4Cooltime = false;
	IsSlot5Cooltime = false;
	IsShopSelectUIMode = false;
	if (!EXP) EXP = 0;
	if (!Gold) Gold = 0;
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

		//쿨타임 UI 초기화
		IngameUI->Skill1CooltimeUI(0.0f, 1.0f);
		IngameUI->Skill2CooltimeUI(0.0f, 10.0f);
		IngameUI->Skill3CooltimeUI(0.0f, 10.0f);
		IngameUI->Skill4CooltimeUI(0.0f, 10.0f);
		IngameUI->Slot1CooltimeUI(0.0f, 10.0f);
		IngameUI->Slot2CooltimeUI(0.0f, 10.0f);
		IngameUI->Slot3CooltimeUI(0.0f, 10.0f);
		IngameUI->Slot4CooltimeUI(0.0f, 10.0f);
		IngameUI->Slot5CooltimeUI(0.0f, 10.0f);
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

	//슬롯 쿨타임 판단
	if (IsSlot1Cooltime)
	{
		IngameUI->Slot1CooltimeUI(GetWorld()->GetTimerManager().GetTimerRemaining(Slot1TimerHandle), Slot1Cooltime);
	}
	if (IsSlot2Cooltime)
	{
		IngameUI->Slot2CooltimeUI(GetWorld()->GetTimerManager().GetTimerRemaining(Slot2TimerHandle), Slot2Cooltime);
	}
	if (IsSlot3Cooltime)
	{
		IngameUI->Slot3CooltimeUI(GetWorld()->GetTimerManager().GetTimerRemaining(Slot3TimerHandle), Slot3Cooltime);
	}
	if (IsSlot4Cooltime)
	{
		IngameUI->Slot4CooltimeUI(GetWorld()->GetTimerManager().GetTimerRemaining(Slot4TimerHandle), Slot4Cooltime);
	}
	if (IsSlot5Cooltime)
	{
		IngameUI->Slot5CooltimeUI(GetWorld()->GetTimerManager().GetTimerRemaining(Slot5TimerHandle), Slot5Cooltime);
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
	PlayerInputComponent->BindAction("MouseMode", IE_Pressed, this, &AMyCharacter::MouseModeOn);
	PlayerInputComponent->BindAction("MouseMode", IE_Released, this, &AMyCharacter::MouseModeOff);

	//퀵슬롯
	PlayerInputComponent->BindAction("Slot1", IE_Pressed, this, &AMyCharacter::UseSlot1);
	PlayerInputComponent->BindAction("Slot2", IE_Pressed, this, &AMyCharacter::UseSlot2);
	PlayerInputComponent->BindAction("Slot3", IE_Pressed, this, &AMyCharacter::UseSlot3);
	PlayerInputComponent->BindAction("Slot4", IE_Pressed, this, &AMyCharacter::UseSlot4);
	PlayerInputComponent->BindAction("Slot5", IE_Pressed, this, &AMyCharacter::UseSlot5);

	//상호작용
	PlayerInputComponent->BindAction("Interaction", IE_Pressed, this, &AMyCharacter::Interact);
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
		InventoryUI = CreateWidget<UInventoryUI>(GetWorld(), InventoryUIClass);
		InventoryUI->InventoryCP = CharacterInventory;
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
			if (CharacterInventory)
			{
				InventoryUI->InventoryCP = CharacterInventory;
			}
			InventoryUI->AddToViewport();

			IsInventoryUIMode = true;

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

	//스텟 적용
	ApplyStat();
}

void AMyCharacter::WeaponDetach()
{
	//무기가 이미 없으면 그냥 종료
	if (!Weapon) return;

	UE_LOG(LogTemp, Log, TEXT("Weapon Detached."));
	Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	Weapon->Destroy();
	Weapon = nullptr;

	//스텟 적용
	ApplyStat();
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

void AMyCharacter::MouseModeOn()
{
	if (PController && !CheckingUI() && !IsOptionUIMode)
	{
		//마우스 모드 켜기
		SetCenterMouse();
		PController->bShowMouseCursor = true;
		PController->SetInputMode(FInputModeGameAndUI());
	}
}

void AMyCharacter::MouseModeOff()
{
	if (PController && !CheckingUI() && !IsOptionUIMode)
	{
		//마우스 모드 끄기
		PController->bShowMouseCursor = false;
		PController->SetInputMode(FInputModeGameOnly());
	}
}

void AMyCharacter::SetCenterMouse()
{
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
	//무기 스텟 적용
	int WSHP = 0;
	int WSAttackDamage = 0;
	int WSCooldown = 0;
	if (Weapon)
	{
		WSHP = Weapon->WSHP;
		WSAttackDamage = Weapon->WSAttackDamage;
		WSCooldown = Weapon->WSCooldown;
	}

	//체력, 공격력 설정(0~...)
	MaxHP = DefaultMaxHP + Level + WSHP;
	AttackDamage = DefaultAttackDamage + Level + WSAttackDamage;
	
	//쿨타임감소 설정(0~50)
	int temp = DefaultCooldown + Level + WSCooldown;
	if (temp >= 50)
	{
		Cooldown = 50;
		//오버 쿨타임은 공격력으로 전환
		AttackDamage += temp - 50;
	}
	else if (temp <= 0)
	{
		Cooldown = 0;
	}
	else
	{
		Cooldown = temp;
	}
	
	//오버 체력 막기
	if (CurrentHP > MaxHP) CurrentHP = MaxHP;

	//최대 경험치량 갱신
	MaxEXPSeting();

	//UI 갱신
	if (IngameUI)
	{
		IngameUI->ChangeHPBar();
		IngameUI->ChangeEXPBar();
		IngameUI->ChangeLevelBar();
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
	DefaultMaxHP = 10;
	DefaultAttackDamage = 10;
	DefaultCooldown = 0;
}

void AMyCharacter::UseSlot1()
{
	if (Slot[0] && !IsSlot1Cooltime)
	{
		IsSlot1Cooltime = true;
		CharacterInventory->UseItem(Slot[0]);
		Slot1Cooltime = 10.0f;
		GetWorld()->GetTimerManager().SetTimer(Slot1TimerHandle, this, &AMyCharacter::Slot1TimerEnd, Slot1Cooltime, false);
	}
	if (!CharacterInventory->CheckItem(Slot[0]))
	{
		Slot[0] = 0;
		if (IngameUI)
		{
			IngameUI->ChangeSlotBar();
		}
	}
}

void AMyCharacter::UseSlot2()
{
	if (Slot[1] && !IsSlot2Cooltime)
	{
		IsSlot2Cooltime = true;
		CharacterInventory->UseItem(Slot[1]);
		Slot2Cooltime = 10.0f;
		GetWorld()->GetTimerManager().SetTimer(Slot2TimerHandle, this, &AMyCharacter::Slot2TimerEnd, Slot2Cooltime, false);
	}
	if (!CharacterInventory->CheckItem(Slot[1]))
	{
		Slot[1] = 0;
		if (IngameUI)
		{
			IngameUI->ChangeSlotBar();
		}
	}
}

void AMyCharacter::UseSlot3()
{
	if (Slot[2] && !IsSlot3Cooltime)
	{
		IsSlot3Cooltime = true;
		CharacterInventory->UseItem(Slot[2]);
		Slot3Cooltime = 10.0f;
		GetWorld()->GetTimerManager().SetTimer(Slot3TimerHandle, this, &AMyCharacter::Slot3TimerEnd, Slot3Cooltime, false);
	}
	if (!CharacterInventory->CheckItem(Slot[2]))
	{
		Slot[2] = 0;
		if (IngameUI)
		{
			IngameUI->ChangeSlotBar();
		}
	}
}

void AMyCharacter::UseSlot4()
{
	if (Slot[3] && !IsSlot4Cooltime)
	{
		IsSlot4Cooltime = true;
		CharacterInventory->UseItem(Slot[3]);
		Slot4Cooltime = 10.0f;
		GetWorld()->GetTimerManager().SetTimer(Slot4TimerHandle, this, &AMyCharacter::Slot4TimerEnd, Slot4Cooltime, false);
	}
	if (!CharacterInventory->CheckItem(Slot[3]))
	{
		Slot[3] = 0;
		if (IngameUI)
		{
			IngameUI->ChangeSlotBar();
		}
	}
}

void AMyCharacter::UseSlot5()
{
	if (Slot[4] && !IsSlot5Cooltime)
	{
		IsSlot5Cooltime = true;
		CharacterInventory->UseItem(Slot[4]);
		Slot5Cooltime = 10.0f;
		GetWorld()->GetTimerManager().SetTimer(Slot5TimerHandle, this, &AMyCharacter::Slot5TimerEnd, Slot5Cooltime, false);
	}
	if (!CharacterInventory->CheckItem(Slot[4]))
	{
		Slot[4] = 0;
		if (IngameUI)
		{
			IngameUI->ChangeSlotBar();
		}
	}
}

void AMyCharacter::Slot1TimerEnd()
{
	IsSlot1Cooltime = false;
}

void AMyCharacter::Slot2TimerEnd()
{
	IsSlot2Cooltime = false;
}

void AMyCharacter::Slot3TimerEnd()
{
	IsSlot3Cooltime = false;
}

void AMyCharacter::Slot4TimerEnd()
{
	IsSlot4Cooltime = false;
}

void AMyCharacter::Slot5TimerEnd()
{
	IsSlot5Cooltime = false;
}

void AMyCharacter::Interact()
{
	//타겟 엑터
	FHitResult Target;

	//캐릭터 기준 바라보는 방향
	FVector Start = GetActorLocation() + FVector(0, 0, 20.0f);
	FVector End = Start + GetControlRotation().Vector() * 300.0f;

	//자신 무시
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	//충돌 체크
	if (GetWorld()->LineTraceSingleByChannel(Target, Start, End, ECC_Visibility, Params))
	{
		if (AActor* HitActor = Target.GetActor())
		{
			ANPC* NPC = Cast<ANPC>(HitActor);
			if (NPC)
			{
				if (ShopSelectUIClass)
				{
					if (!ShopSelectUI)
					{
						ShopSelectUI = CreateWidget<USelectShop>(GetWorld(), ShopSelectUIClass);
						ShopSelectUI->Player = this;
					}

					if (ShopSelectUI->IsInViewport())
					{
						ShopSelectUI->RemoveFromParent();
						PController->SetShowMouseCursor(false);
						PController->SetInputMode(FInputModeGameOnly());
						ShopSelectUI = nullptr;
					}
					else
					{
						//다른 UI 제거
						if (CheckingUI())
						{
							ShutdownAllUI();
						}
						ShopSelectUI->AddToViewport();
						PController->SetShowMouseCursor(true);
						PController->SetInputMode(FInputModeUIOnly());
						PController->FlushPressedKeys();
					}
				}
				
			}
		}
	}
}