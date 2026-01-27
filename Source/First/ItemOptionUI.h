// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "ItemStructure.h"
#include "ItemOptionUI.generated.h"

/**
 * 
 */
UCLASS()
class FIRST_API UItemOptionUI : public UUserWidget
{
	GENERATED_BODY()
	
	void NativeConstruct();
	int ItemID;
	int Count;

	UPROPERTY(meta = (BindWidget)) UButton* UseButton;
	UPROPERTY(meta = (BindWidget)) UButton* Slot1Button;
	UPROPERTY(meta = (BindWidget)) UButton* Slot2Button;
	UPROPERTY(meta = (BindWidget)) UButton* Slot3Button;
	UPROPERTY(meta = (BindWidget)) UButton* Slot4Button;
	UPROPERTY(meta = (BindWidget)) UButton* Slot5Button;
	UPROPERTY(meta = (BindWidget)) UButton* ReleaseSlotButton;
	UPROPERTY(meta = (BindWidget)) UButton* RemoveButton;

public:
	//아이템 정보 확인
	UFUNCTION(BlueprintCallable) void CheckItemInfo(int ItemIDValue, int CountValue, EItemType ItemTypeValue);
	UFUNCTION() void UseButtonClick();
	UFUNCTION() void Slot1ButtonClick();
	UFUNCTION() void Slot2ButtonClick();
	UFUNCTION() void Slot3ButtonClick();
	UFUNCTION() void Slot4ButtonClick();
	UFUNCTION() void Slot5ButtonClick();
	UFUNCTION() void ReleaseSlotButtonClick();
	UFUNCTION() void RemoveButtonClick();

	//UI 제거
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
};
