// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "BowBase.generated.h"

/**
 * 
 */
UCLASS()
class FIRST_API ABowBase : public AWeaponBase
{
	GENERATED_BODY()
	
protected:
	ABowBase();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon") USkeletalMeshComponent* WeaponMesh;
};
