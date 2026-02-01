// Fill out your copyright notice in the Description page of Project Settings.


#include "Shop.h"

void UShop::NativeConstruct()
{
	Super::NativeConstruct();

	CloseButton->OnClicked.AddDynamic(this, &UShop::CloseButtonClick);
}

void UShop::CloseButtonClick()
{
	UE_LOG(LogTemp, Log, TEXT("Clicked Close Button."));
	if (Player)
	{
		UE_LOG(LogTemp, Log, TEXT("Cast Success."));
		Player->PController->SetShowMouseCursor(false);
		Player->PController->SetInputMode(FInputModeGameOnly());
		RemoveFromParent();
	}
}