// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemUI.h"

void UItemUI::SetItemInfo(int ItemIDValue, int CountValue, UTexture2D* IconValue, FName& NameValue, FString& DescriptionValue, EItemType ItemTypeValue)
{
    ItemName = NameValue;
    ItemID = ItemIDValue;
    Count = CountValue;
    Description = DescriptionValue;
    ItemType = ItemTypeValue;

    if (ItemIconImage) ItemIconImage->SetBrushFromTexture(IconValue);
    if (CountText) CountText->SetText(FText::AsNumber(Count));
    if (NameText) NameText->SetText(FText::FromName(NameValue));
}

void UItemUI::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

    //플레이어 정보 가져오기
    APlayerController* PC = GetOwningPlayer();
    if (!PC) return;

    if (TooltipClass)
    {
        if (!Tooltip)
        {
            Tooltip = CreateWidget<UTooltipUI>(GetWorld(), TooltipClass);
        }

        Tooltip->SetItemData(ItemName, ItemType, Description);

        //마우스 위치 정보 가져오기
        FVector2D MousePos;
        PC->GetMousePosition(MousePos.X, MousePos.Y);
        Tooltip->SetPositionInViewport(MousePos, true);

        Tooltip->AddToViewport(100);
    }
}

void UItemUI::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
    Super::NativeOnMouseLeave(InMouseEvent);

    if (Tooltip)
    {
        Tooltip->RemoveFromParent();
        Tooltip = nullptr;
    }
}

void UItemUI::NativeDestruct()
{
    Super::NativeDestruct();

    if (Tooltip)
    {
        Tooltip->RemoveFromParent();
        Tooltip = nullptr;
    }
}