// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemStructure.h"
#include "Components/TextBlock.h"
#include "TooltipUI.generated.h"

/**
 * 
 */
UCLASS()
class FIRST_API UTooltipUI : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetItemData(FName& NameValue, EItemType ItemTypeValue, FString& DescriptionValue, int GoldValue);

	UPROPERTY(meta = (BindWidget)) UTextBlock* Name;
	UPROPERTY(meta = (BindWidget)) UTextBlock* ItemType;
	UPROPERTY(meta = (BindWidget)) UTextBlock* Description;
	UPROPERTY(meta = (BindWidget)) UTextBlock* GoldValueText;
};
