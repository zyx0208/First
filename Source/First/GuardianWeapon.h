// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LongswordBase.h"
#include "GuardianWeapon.generated.h"

/**
 * 
 */
UCLASS()
class FIRST_API AGuardianWeapon : public ALongswordBase
{
	GENERATED_BODY()

	AGuardianWeapon();

public:
	virtual void SetupSkills() override;
};
