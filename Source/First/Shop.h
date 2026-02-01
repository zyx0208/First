// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyCharacter.h"
#include "Shop.generated.h"

/**
 * 
 */
UCLASS()
class FIRST_API UShop : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeConstruct();

	AMyCharacter* Player;

	UPROPERTY(meta = (BindWidget)) UButton* CloseButton;

	//상호작용 함수
	UFUNCTION() void CloseButtonClick();
};
