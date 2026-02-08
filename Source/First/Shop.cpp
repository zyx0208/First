// Fill out your copyright notice in the Description page of Project Settings.


#include "Shop.h"

void UShop::NativeConstruct()
{
	Super::NativeConstruct();

	Player->IsShop = true;
	InventoryCP = Player->CharacterInventory;

	CloseButton->OnClicked.AddDynamic(this, &UShop::CloseButtonClick);

	InventorySeting();
	ShopSeting();
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
	Player->IsShop = false;
}

void UShop::InventorySeting()
{
	if (!PlayerWrapBox || !InventoryCP) return;

	PlayerWrapBox->ClearChildren();
	UE_LOG(LogTemp, Log, TEXT("PlayerItemClear."));

	for (FInventoryItemStructure& Item : InventoryCP->InventoryItems)
	{
		if (!ItemUIClass) continue;

		UItemUI* NewSlot = CreateWidget<UItemUI>(GetWorld(), ItemUIClass);
		if (NewSlot)
		{
			// DataTable에서 아이템 정보 조회
			FItemStructure* ItemData = InventoryCP->GetItemData(Item.ItemID);
			if (ItemData)
			{
				NewSlot->SetItemInfo(Item.ItemID, Item.Stack, ItemData->ItemIcon, ItemData->ItemName, ItemData->Description, ItemData->ItemType, ItemData->GoldValue);
				NewSlot->OwnerType = EItemOwnerType::Player;
				PlayerWrapBox->AddChild(NewSlot);
				UE_LOG(LogTemp, Log, TEXT("ItemUI Add : %d"), Item.ItemID);
			}
		}
	}
}

void UShop::ShopSeting()
{
	//테스트용 캐릭터 인벤토리 설정
	if (!ShopWrapBox || !InventoryCP) return;

	ShopWrapBox->ClearChildren();
	UE_LOG(LogTemp, Log, TEXT("ShopItemClear."));

	for (FInventoryItemStructure& Item : InventoryCP->InventoryItems)
	{
		if (!ItemUIClass) continue;

		UItemUI* NewSlot = CreateWidget<UItemUI>(GetWorld(), ItemUIClass);
		if (NewSlot)
		{
			// DataTable에서 아이템 정보 조회
			FItemStructure* ItemData = InventoryCP->GetItemData(Item.ItemID);
			if (ItemData)
			{
				NewSlot->SetItemInfo(Item.ItemID, Item.Stack, ItemData->ItemIcon, ItemData->ItemName, ItemData->Description, ItemData->ItemType, ItemData->GoldValue);
				NewSlot->OwnerType = EItemOwnerType::NPC;
				ShopWrapBox->AddChild(NewSlot);
				UE_LOG(LogTemp, Log, TEXT("ItemUI Add : %d"), Item.ItemID);
			}
		}
	}
}