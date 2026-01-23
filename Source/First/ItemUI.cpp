// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemUI.h"

void UItemUI::SetItemInfo(int ItemIDValue, int CountValue, UTexture2D* IconValue, FName& NameValue, FString& DescriptionValue)
{
    ItemID = ItemIDValue;
    Count = CountValue;
    Description = DescriptionValue;

    if (ItemIconImage) ItemIconImage->SetBrushFromTexture(IconValue);
    if (CountText) CountText->SetText(FText::AsNumber(Count));
    if (NameText) NameText->SetText(FText::FromName(NameValue));
}