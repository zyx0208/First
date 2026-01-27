// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MySaveGame.generated.h"

/**
 * 
 */
UCLASS()
class FIRST_API UMySaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
    
    //마스터음량
    UPROPERTY(VisibleAnywhere) float MasterVolume = 1.0f;

    //배경음악
    UPROPERTY(VisibleAnywhere) float BGMVolume = 1.0f;

    //효과음
    UPROPERTY(VisibleAnywhere) float SFXVolume = 1.0f;
};
