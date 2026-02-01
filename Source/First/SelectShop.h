// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyCharacter.h"
#include "Shop.h"
#include "ChangeWeapon.h"
#include "SelectShop.generated.h"

class AMyCharacter;

UCLASS()
class FIRST_API USelectShop : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeConstruct();

	AMyCharacter* Player;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI") TSubclassOf<UShop> ShopUIClass;
	UShop* ShopUI;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI") TSubclassOf<UChangeWeapon> ChangeWeaponUIClass;
	UChangeWeapon* ChangeWeaponUI;

	UPROPERTY(meta = (BindWidget)) UButton* CloseButton;
	UPROPERTY(meta = (BindWidget)) UButton* SelectShopButton1;
	UPROPERTY(meta = (BindWidget)) UButton* SelectShopButton2;

	//상호작용 함수
	UFUNCTION() void CloseButtonClick();
	UFUNCTION() void SelectShopButton1Click();
	UFUNCTION() void SelectShopButton2Click();

	//애니메이션
	UPROPERTY(meta = (BindWidgetAnim), Transient) UWidgetAnimation* OpenAnim;
};
