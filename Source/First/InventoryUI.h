// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/WrapBox.h"
#include "ItemUI.h"
#include "InventoryUI.generated.h"

class AMyCharacter;
class UInventoryComponent;

UCLASS()
class FIRST_API UInventoryUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//플레이어 정보 불러오기
	UInventoryComponent* InventoryCP;
	AMyCharacter* PC;

	void NativeConstruct();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TSubclassOf<UItemUI> ItemUIClass;

	//위젯
	UPROPERTY(meta = (BindWidget)) UButton* CloseButton;
	UPROPERTY(meta = (BindWidget)) UTextBlock* HPText;
	UPROPERTY(meta = (BindWidget)) UTextBlock* AttackDamageText;
	UPROPERTY(meta = (BindWidget)) UTextBlock* CooldownText;
	UPROPERTY(meta = (BindWidget)) UWrapBox* ItemWrapBox;

	//UPROPERTY(meta = (BindWidget)) UTextBlock* LevelText;
	//상호작용 함수
	UFUNCTION() void CloseButtonClick();
	UFUNCTION() void InventorySeting();

	//애니메이션
	UPROPERTY(meta = (BindWidgetAnim), Transient) UWidgetAnimation* OpenAnim;
};
