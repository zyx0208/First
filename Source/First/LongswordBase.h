// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "LongswordBase.generated.h"

/**
 * 
 */
UCLASS()
class FIRST_API ALongswordBase : public AWeaponBase
{
	GENERATED_BODY()

protected:
	ALongswordBase();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon") UStaticMeshComponent* WeaponMesh;
};
