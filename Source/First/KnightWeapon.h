// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LongswordBase.h"
#include "KnightWeapon.generated.h"

/**
 * 
 */
UCLASS()
class FIRST_API AKnightWeapon : public ALongswordBase
{
	GENERATED_BODY()
	
    AKnightWeapon();
public:
    virtual void SetupSkills() override;

protected:
    //무사 전용 스킬
    void ShieldBash();
};
