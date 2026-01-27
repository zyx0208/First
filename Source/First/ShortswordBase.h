// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "ShortswordBase.generated.h"

/**
 * 
 */
UCLASS()
class FIRST_API AShortswordBase : public AWeaponBase
{
	GENERATED_BODY()
	
protected:
	AShortswordBase();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon") UStaticMeshComponent* WeaponMesh;
};
