// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "MageBase.generated.h"

/**
 * 
 */
UCLASS()
class FIRST_API AMageBase : public AWeaponBase
{
	GENERATED_BODY()
	
protected:
	AMageBase();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon") UStaticMeshComponent* WeaponMesh;
};
