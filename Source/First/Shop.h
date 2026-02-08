// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyCharacter.h"
#include "Components/WrapBox.h"
#include "InventoryComponent.h"
#include "ItemUI.h"
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
	UInventoryComponent* InventoryCP;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TSubclassOf<UItemUI> ItemUIClass;

	//캐릭터 인벤토리 세팅
	void InventorySeting();
	//상점 인벤토리 세팅
	void ShopSeting();

	UPROPERTY(meta = (BindWidget)) UButton* CloseButton;
	UPROPERTY(meta = (BindWidget)) UWrapBox* PlayerWrapBox;
	UPROPERTY(meta = (BindWidget)) UWrapBox* ShopWrapBox;

	//상호작용 함수
	UFUNCTION() void CloseButtonClick();
};
