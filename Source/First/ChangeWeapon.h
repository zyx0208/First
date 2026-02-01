// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyCharacter.h"
#include "Components/TextBlock.h"
#include "WeaponBase.h"
#include "KnightWeapon.h"
#include "GuardianWeapon.h"
#include "LongbowWeapon.h"
#include "ShortbowWeapon.h"
#include "MageWeapon.h"
#include "WhitemageWeapon.h"
#include "AssassinWeapon.h"
#include "ThrowerWeapon.h"
#include "ChangeWeapon.generated.h"

/**
 * 
 */
UCLASS()
class FIRST_API UChangeWeapon : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeConstruct();

	AMyCharacter* Player;

	UPROPERTY(meta = (BindWidget)) UButton* CloseButton;
	UPROPERTY(meta = (BindWidget)) UButton* ChangeWeaponButton1;
	UPROPERTY(meta = (BindWidget)) UButton* ChangeWeaponButton2;
	UPROPERTY(meta = (BindWidget)) UTextBlock* ChangeWeaponButton1Text;
	UPROPERTY(meta = (BindWidget)) UTextBlock* ChangeWeaponButton2Text;

	//UI 텍스트용 체크 함수
	int Preset;

	//상호작용 함수
	UFUNCTION() void CloseButtonClick();
	UFUNCTION() void SelectShopButton1Click();
	UFUNCTION() void SelectShopButton2Click();

	//전직용 무기BP 클래스
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon") TSubclassOf<AKnightWeapon> Weapon1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon") TSubclassOf<AGuardianWeapon> Weapon2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon") TSubclassOf<ALongbowWeapon> Weapon3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon") TSubclassOf<AShortbowWeapon> Weapon4;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon") TSubclassOf<AMageWeapon> Weapon5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon") TSubclassOf<AWhitemageWeapon> Weapon6;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon") TSubclassOf<AAssassinWeapon> Weapon7;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon") TSubclassOf<AThrowerWeapon> Weapon8;
};
