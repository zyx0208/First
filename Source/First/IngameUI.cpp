// Fill out your copyright notice in the Description page of Project Settings.


#include "IngameUI.h"
#include "MyCharacter.h"

void UIngameUI::NativeConstruct()
{
	Super::NativeConstruct();

	//이벤트 할당
	OptionButton->OnClicked.AddDynamic(this, &UIngameUI::OptionButtonClick);
	InventoryButton->OnClicked.AddDynamic(this, &UIngameUI::InventoryButtonClick);;
	SkillButton->OnClicked.AddDynamic(this, &UIngameUI::SkillButtonClick);;
}

void UIngameUI::SetPlayer(AMyCharacter* Player)
{
	PC = Player;
}

void UIngameUI::OptionButtonClick()
{
	if (PC) PC->ToggleOption();
}

void UIngameUI::InventoryButtonClick()
{
	if (PC) PC->ToggleInventory();
}

void UIngameUI::SkillButtonClick()
{
	if (PC) PC->ToggleSkill();
}