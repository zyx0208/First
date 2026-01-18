// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryUI.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/Button.h"
#include "MyCharacter.h"

void UInventoryUI::NativeConstruct()
{
	Super::NativeConstruct();

	//이벤트 할당
	CloseButton->OnClicked.AddDynamic(this, &UInventoryUI::CloseButtonClick);
}

void UInventoryUI::CloseButtonClick()
{
	UE_LOG(LogTemp, Log, TEXT("Clicked Close Button."));
	AMyCharacter* PCharacter = Cast<AMyCharacter>(GetOwningPlayerPawn());
	if (PCharacter)
	{
		UE_LOG(LogTemp, Log, TEXT("Cast Success."));
		PCharacter->ToggleInventory();
	}
}