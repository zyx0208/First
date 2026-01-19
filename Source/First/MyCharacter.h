// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WeaponBase.h"
#include "MyCharacter.generated.h"

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI") TSubclassOf<UUserWidget> InventoryUIClass;
	UUserWidget* InventoryUI;
	//UI모드를 확인하는 변수
	bool IsInventoryUIMode;

	//인벤토리UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI") TSubclassOf<UUserWidget> SkillUIClass;
	UUserWidget* SkillUI;
	//UI모드를 확인하는 변수
	bool IsSkillUIMode;

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
};
