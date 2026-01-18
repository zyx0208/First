// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

UCLASS()
class FIRST_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeaponBase();

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
