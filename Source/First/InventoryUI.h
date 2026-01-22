// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "MyCharacter.h"
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
	//플레이어 정보 불러오기
	AMyCharacter* PC;
	//위젯
	UPROPERTY(meta = (BindWidget)) UButton* CloseButton;
	UPROPERTY(meta = (BindWidget)) UTextBlock* HPText;
	UPROPERTY(meta = (BindWidget)) UTextBlock* AttackDamageText;
	UPROPERTY(meta = (BindWidget)) UTextBlock* CooldownText;
	//UPROPERTY(meta = (BindWidget)) UTextBlock* LevelText;
	//상호작용 함수
	UFUNCTION() void CloseButtonClick();
};
