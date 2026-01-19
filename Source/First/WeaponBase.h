// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponAttack.h"
#include "WeaponBase.generated.h"

//스킬를 델리게이트를 통해 관리
DECLARE_DELEGATE(FSkillDelegate);

UCLASS()
class FIRST_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeaponBase();

	//모든 스킬들을 델리게이트에 저장
	TArray<FSkillDelegate> AllSkills;
	
	//정수값(0~3)을 통해 스킬 실행 
	virtual void UseSkill(int Slot);

	//델리게이트 배열에 등록하는 함수
	virtual void SetupSkills();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	//루트 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")USceneComponent* Root;
	//체력 계수
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WeaponStat")float HPRate;
	//공격력 계수
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WeaponStat")float AttackDamageRate;
	//공격속도 및 쿨타임 계수
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WeaponStat")float AttackSpeedRate;

};
