// Fill out your copyright notice in the Description page of Project Settings.


#include "TooltipUI.h"

void UTooltipUI::SetItemData(FName& NameValue, EItemType ItemTypeValue, FString& DescriptionValue)
{
	Name->SetText(FText::FromName(NameValue));
	Description->SetText(FText::FromString(DescriptionValue));

	//한글화를 위한 스위치문
	switch (ItemTypeValue)
	{
	case EItemType::Equipment:
		ItemType->SetText(FText::FromString(TEXT("장비")));
		break;
	case EItemType::SkillBook:
		ItemType->SetText(FText::FromString(TEXT("스킬북")));
		break;
	case EItemType::Consumable:
		ItemType->SetText(FText::FromString(TEXT("소비 아이템")));
		break;
	case EItemType::NonConsumable:
		ItemType->SetText(FText::FromString(TEXT("재료 아이템")));
		break;
	default:
		break;
	}
}