// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryUI.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/Button.h"
#include "MyCharacter.h"

void UInventoryUI::NativeConstruct()
{
	Super::NativeConstruct();

	//플레이어 불러오기
	PC = Cast<AMyCharacter>(GetOwningPlayerPawn());

	//이벤트 할당
	CloseButton->OnClicked.AddDynamic(this, &UInventoryUI::CloseButtonClick);

	//텍스트 할당
	if (PC)
	{
		FText HT = FText::FromString(FString::Printf(TEXT("체력 : %d / %d"), PC->CurrentHP, PC->MaxHP));
		HPText->SetText(HT);
		FText ADT = FText::FromString(FString::Printf(TEXT("공격력 : %d"), PC->AttackDamage));
		AttackDamageText->SetText(ADT);
		FText CDT = FText::FromString(FString::Printf(TEXT("쿨타임감소 : %d%%"), PC->Cooldown));
		CooldownText->SetText(CDT);
	}
}

void UInventoryUI::CloseButtonClick()
{
	UE_LOG(LogTemp, Log, TEXT("Clicked Close Button."));
	if (PC)
	{
		UE_LOG(LogTemp, Log, TEXT("Cast Success."));
		PC->ToggleInventory();
	}
}

