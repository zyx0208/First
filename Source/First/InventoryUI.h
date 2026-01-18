// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "InventoryUI.generated.h"

/**
 * 
 */
UCLASS()
class FIRST_API UInventoryUI : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	void NativeConstruct();
	//위젯
	UPROPERTY(meta = (BindWidget)) UButton* CloseButton;

	//상호작용 함수
	UFUNCTION() void CloseButtonClick();
};
