// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WeaponBase.h"
#include "IngameUI.h"
#include "InventoryComponent.h"
#include "MyCharacter.generated.h"

class UInventoryUI;

UCLASS()
class FIRST_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMyCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//옵션UI함수
	void ToggleOption();

	//인벤토리UI함수
	void ToggleInventory();

	//스킬UI함수
	void ToggleSkill();

	//무기 장착 함수
	UFUNCTION(BlueprintCallable) void WeaponAttach(TSubclassOf<AWeaponBase> TargetWeapon);
	//무기 해제 함수
	UFUNCTION(BlueprintCallable) void WeaponDetach();
	//무기를 장착하고 있는가?
	bool IsAttachWeapon;
	//무기 정보
	UPROPERTY() AWeaponBase* Weapon;
	//무기 위치 세팅를 위한 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) USceneComponent* WeaponPosition;
	//인벤토리 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) UInventoryComponent* CharacterInventory;

	//사용 스킬 인덱스 [0 : 1번스킬인덱스값] [1 : 2번스킬인덱스값] [2 : 3번스킬인덱스값] [3 : 4번스킬인덱스값]
	int SKillIdx[4];

	//1번 스킬 사용
	void UseSkill1();
	//2번 스킬 사용
	void UseSkill2();
	//3번 스킬 사용
	void UseSkill3();
	//4번 스킬 사용
	void UseSkill4();

	//1번 스킬 쿨타임
	FTimerHandle Skill1TimerHandle;
	void Skill1TimerEnd();
	bool IsSkill1Cooltime;
	float Skill1Cooltime;
	//2번 스킬 쿨타임
	FTimerHandle Skill2TimerHandle;
	void Skill2TimerEnd();
	bool IsSkill2Cooltime;
	float Skill2Cooltime;
	//3번 스킬 쿨타임
	FTimerHandle Skill3TimerHandle;
	void Skill3TimerEnd();
	bool IsSkill3Cooltime;
	float Skill3Cooltime;
	//4번 스킬 쿨타임
	FTimerHandle Skill4TimerHandle;
	void Skill4TimerEnd();
	bool IsSkill4Cooltime;
	float Skill4Cooltime;

	//최대체력
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) int MaxHP;
	//현재체력
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) int CurrentHP;
	//공격력
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) int AttackDamage;
	//레벨
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) int Level;
	//최대 경험치량
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) int MaxEXP;
	//경험치량
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) int EXP;
	//쿨타임 감소 옵션
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) int Cooldown;
	
	//디폴트 최대 체력(레벨에 따른 스탯)
	int DefaultMaxHP;
	//디폴트 공격력 옵션(레벨에 따른 스탯)
	int DefaultAttackDamage;
	//디폴트 쿨타임 옵션(레벨에 따른 스탯)
	int DefaultCooldown;

	//회복 함수
	UFUNCTION(BlueprintCallable) void HealHP(int value);
	//레벨업 함수
	UFUNCTION(BlueprintCallable) void LevelUp();
	//피격 함수
	UFUNCTION(BlueprintCallable) void Attacked(int value);
	//사망 함수
	void Death();
	//경험치 획득 함수
	UFUNCTION(BlueprintCallable) void AddEXP(int value);
	//현재 체력 퍼센트 반환함수
	float HPPercent();
	//현재 경험치 퍼센트 반환함수
	float EXPPercent();
	//최종 [체력, 공격력, 쿨타임]값
	UFUNCTION(BlueprintCallable) void ApplyStat();
	//최대 경험치량 설정
	UFUNCTION(BlueprintCallable) void MaxEXPSeting();
	//레벨 1로 초기화(테스트용 함수)
	UFUNCTION(BlueprintCallable) void ResetLevel();



protected:
	virtual void BeginPlay() override;

	//이동 설정
	void MoveForward(float value);
	void MoveRight(float value);

	//이동속도
	float MoveSpeed;

	//이동 여부
	UPROPERTY(BlueprintReadOnly) bool IsWalk;

	//달리기
	void StartRun();
	void StopRun();

	//달리기 여부
	UPROPERTY(BlueprintReadOnly) bool IsRun;

	//시점 설정
	void Turn(float value);
	void LookUp(float value);
	
	//옵션UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI") TSubclassOf<UUserWidget> OptionUIClass;
	UUserWidget* OptionUI;
	//UI모드를 확인하는 변수
	bool IsOptionUIMode;

	//인벤토리UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI") TSubclassOf<UInventoryUI> InventoryUIClass;
	UInventoryUI* InventoryUI;
	//UI모드를 확인하는 변수
	bool IsInventoryUIMode;

	//인벤토리UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI") TSubclassOf<UUserWidget> SkillUIClass;
	UUserWidget* SkillUI;
	//UI모드를 확인하는 변수
	bool IsSkillUIMode;

	//인게임UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI") TSubclassOf<UIngameUI> IngameUIClass;
	UIngameUI* IngameUI;

	//옵션 UI를 제외하고 UI가 켜져있는지 확인하는 함수
	bool CheckingUI();

	//옵션 UI를 제외하고 모든 UI를 꺼버리는 함수
	void ShutdownAllUI();

	//점프함수
	void StartJump();

	//크로스헤어UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI") TSubclassOf<UUserWidget> CrosshairUIClass;
	UUserWidget* CrosshairUI;

	//크로스헤어UI 생성함수
	void ToggleCrosshair();

	//마우스모드
	void MouseModeOn();
	//마우스모드
	void MouseModeOff();

	//마우스 위치 중앙 설정
	void SetCenterMouse();

	void DefaultStatSeting();
};
