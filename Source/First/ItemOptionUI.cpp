// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemOptionUI.h"
#include "MyCharacter.h"

void UItemOptionUI::NativeConstruct()
{
	UseButton->OnClicked.AddDynamic(this, &UItemOptionUI::UseButtonClick);
	Slot1Button->OnClicked.AddDynamic(this, &UItemOptionUI::Slot1ButtonClick);
	Slot2Button->OnClicked.AddDynamic(this, &UItemOptionUI::Slot2ButtonClick);
	Slot3Button->OnClicked.AddDynamic(this, &UItemOptionUI::Slot3ButtonClick);
	Slot4Button->OnClicked.AddDynamic(this, &UItemOptionUI::Slot4ButtonClick);
	Slot5Button->OnClicked.AddDynamic(this, &UItemOptionUI::Slot5ButtonClick);
	ReleaseSlotButton->OnClicked.AddDynamic(this, &UItemOptionUI::ReleaseSlotButtonClick);
	RemoveButton->OnClicked.AddDynamic(this, &UItemOptionUI::RemoveButtonClick);
}

void UItemOptionUI::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
    Super::NativeOnMouseLeave(InMouseEvent);

	RemoveFromParent();
}

void UItemOptionUI::CheckItemInfo(int ItemIDValue, int CountValue, EItemType ItemTypeValue)
{
	ItemID = ItemIDValue;
	Count = CountValue;

	switch (ItemTypeValue)
	{
	case EItemType::Equipment:
		Slot1Button->SetVisibility(ESlateVisibility::Collapsed);
		Slot2Button->SetVisibility(ESlateVisibility::Collapsed);
		Slot3Button->SetVisibility(ESlateVisibility::Collapsed);
		Slot4Button->SetVisibility(ESlateVisibility::Collapsed);
		Slot5Button->SetVisibility(ESlateVisibility::Collapsed);
		break;
	case EItemType::SkillBook:
		Slot1Button->SetVisibility(ESlateVisibility::Collapsed);
		Slot2Button->SetVisibility(ESlateVisibility::Collapsed);
		Slot3Button->SetVisibility(ESlateVisibility::Collapsed);
		Slot4Button->SetVisibility(ESlateVisibility::Collapsed);
		Slot5Button->SetVisibility(ESlateVisibility::Collapsed);
		ReleaseSlotButton->SetVisibility(ESlateVisibility::Collapsed);
		break;
	case EItemType::Consumable:
		UseButton->SetVisibility(ESlateVisibility::Collapsed);
		break;
	case EItemType::NonConsumable:
		UseButton->SetVisibility(ESlateVisibility::Collapsed);
		Slot1Button->SetVisibility(ESlateVisibility::Collapsed);
		Slot2Button->SetVisibility(ESlateVisibility::Collapsed);
		Slot3Button->SetVisibility(ESlateVisibility::Collapsed);
		Slot4Button->SetVisibility(ESlateVisibility::Collapsed);
		Slot5Button->SetVisibility(ESlateVisibility::Collapsed);
		ReleaseSlotButton->SetVisibility(ESlateVisibility::Collapsed);
		break;
	default:
		break;
	}
}

void UItemOptionUI::UseButtonClick()
{
	if (APlayerController* PC = GetOwningPlayer())
	{
		AMyCharacter* Player = Cast<AMyCharacter>(PC->GetPawn());
		if (Player)
		{
			//asdf
		}
	}
}

void UItemOptionUI::Slot1ButtonClick()
{
	if (APlayerController* PC = GetOwningPlayer())
	{
		AMyCharacter* Player = Cast<AMyCharacter>(PC->GetPawn());
		if (Player)
		{
			for (int i = 0; i < 5; i++)
			{
				if (Player->Slot[i] == ItemID)
				{
					Player->Slot[i] = 0;
				}
			}
			Player->Slot[0] = ItemID;
			if (Player->IngameUI)
			{
				Player->IngameUI->ChangeSlotBar();
			}
		}
	}
}

void UItemOptionUI::Slot2ButtonClick()
{
	if (APlayerController* PC = GetOwningPlayer())
	{
		AMyCharacter* Player = Cast<AMyCharacter>(PC->GetPawn());
		if (Player)
		{
			for (int i = 0; i < 5; i++)
			{
				if (Player->Slot[i] == ItemID)
				{
					Player->Slot[i] = 0;
				}
			}
			Player->Slot[1] = ItemID;
			if (Player->IngameUI)
			{
				Player->IngameUI->ChangeSlotBar();
			}
		}
	}
}

void UItemOptionUI::Slot3ButtonClick()
{
	if (APlayerController* PC = GetOwningPlayer())
	{
		AMyCharacter* Player = Cast<AMyCharacter>(PC->GetPawn());
		if (Player)
		{
			for (int i = 0; i < 5; i++)
			{
				if (Player->Slot[i] == ItemID)
				{
					Player->Slot[i] = 0;
				}
			}
			Player->Slot[2] = ItemID;
			if (Player->IngameUI)
			{
				Player->IngameUI->ChangeSlotBar();
			}
		}
	}
}

void UItemOptionUI::Slot4ButtonClick()
{
	if (APlayerController* PC = GetOwningPlayer())
	{
		AMyCharacter* Player = Cast<AMyCharacter>(PC->GetPawn());
		if (Player)
		{
			for (int i = 0; i < 5; i++)
			{
				if (Player->Slot[i] == ItemID)
				{
					Player->Slot[i] = 0;
				}
			}
			Player->Slot[3] = ItemID;
			if (Player->IngameUI)
			{
				Player->IngameUI->ChangeSlotBar();
			}
		}
	}
}

void UItemOptionUI::Slot5ButtonClick()
{
	if (APlayerController* PC = GetOwningPlayer())
	{
		AMyCharacter* Player = Cast<AMyCharacter>(PC->GetPawn());
		if (Player)
		{
			for (int i = 0; i < 5; i++)
			{
				if (Player->Slot[i] == ItemID)
				{
					Player->Slot[i] = 0;
				}
			}
			Player->Slot[4] = ItemID;
			if (Player->IngameUI)
			{
				Player->IngameUI->ChangeSlotBar();
			}
		}
	}
}

void UItemOptionUI::ReleaseSlotButtonClick()
{
	if (APlayerController* PC = GetOwningPlayer())
	{
		AMyCharacter* Player = Cast<AMyCharacter>(PC->GetPawn());
		if (Player)
		{
			for (int i = 0; i < 5; i++)
			{
				if (Player->Slot[i] == ItemID)
				{
					Player->Slot[i] = 0;
				}
			}
			if (Player->IngameUI)
			{
				Player->IngameUI->ChangeSlotBar();
			}
		}
	}
}

void UItemOptionUI::RemoveButtonClick()
{
	if (APlayerController* PC = GetOwningPlayer())
	{
		AMyCharacter* Player = Cast<AMyCharacter>(PC->GetPawn());
		if (Player)
		{
			//아이템 제거
			Player->CharacterInventory->RemoveItem(ItemID, 1);

			//0개가 되면 퀵슬롯도 제거
			if (!Player->CharacterInventory->CheckItem(ItemID))
			{
				for (int i = 0; i < 5; i++)
				{
					if (Player->Slot[i] == ItemID)
					{
						Player->Slot[i] = 0;
					}
				}
			}

			if (Player->IngameUI)
			{
				Player->IngameUI->ChangeSlotBar();
			}
		}
	}
}

