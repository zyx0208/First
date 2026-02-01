// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectShop.h"
#include "MyCharacter.h"


void USelectShop::NativeConstruct()
{
	Super::NativeConstruct();

	CloseButton->OnClicked.AddDynamic(this, &USelectShop::CloseButtonClick);
	SelectShopButton1->OnClicked.AddDynamic(this, &USelectShop::SelectShopButton1Click);
	SelectShopButton2->OnClicked.AddDynamic(this, &USelectShop::SelectShopButton2Click);

	if (OpenAnim)
	{
		PlayAnimation(OpenAnim);
	}

	Player->SetCenterMouse();
}

void USelectShop::CloseButtonClick()
{
	UE_LOG(LogTemp, Log, TEXT("Clicked Close Button."));
	if (Player)
	{
		UE_LOG(LogTemp, Log, TEXT("Cast Success."));
		Player->ShopSelectUI->RemoveFromParent();
		Player->PController->SetShowMouseCursor(false);
		Player->PController->SetInputMode(FInputModeGameOnly());
		Player->ShopSelectUI = nullptr;
	}
}

void USelectShop::SelectShopButton1Click()
{
	if (ChangeWeaponUIClass)
	{
		if (!ChangeWeaponUI)
		{
			UE_LOG(LogTemp, Log, TEXT("Create ChangeWeaponUI."));
			ChangeWeaponUI = CreateWidget<UChangeWeapon>(GetWorld(), ChangeWeaponUIClass);
			ChangeWeaponUI->Player = Player;
		}
		if (!ChangeWeaponUI->IsInViewport())
		{
			UE_LOG(LogTemp, Log, TEXT("Add to viewport ChangeWeaponUI."));
			ChangeWeaponUI->AddToViewport();
			Player->ShopSelectUI->RemoveFromParent();
			Player->ShopSelectUI = nullptr;
		}
	}
}

void USelectShop::SelectShopButton2Click()
{
	if (ShopUIClass)
	{
		if (!ShopUI)
		{
			UE_LOG(LogTemp, Log, TEXT("Create ShopUI."));
			ShopUI = CreateWidget<UShop>(GetWorld(), ShopUIClass);
			ShopUI->Player = Player;
		}
		if (!ShopUI->IsInViewport())
		{
			UE_LOG(LogTemp, Log, TEXT("Add to viewport ShopUI."));
			ShopUI->AddToViewport();
			Player->ShopSelectUI->RemoveFromParent();
			Player->ShopSelectUI = nullptr;
		}
	}
}