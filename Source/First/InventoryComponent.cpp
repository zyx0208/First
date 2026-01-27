// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "InventoryUI.h"
#include "MyCharacter.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FItemStructure* UInventoryComponent::GetItemData(int ItemID)
{
	//데이터베이스가 없을 경우 null 반환
	if (!ItemDataTable) return nullptr;

	//ItemID로 DataTable 전체 순회
	for (auto& Row : ItemDataTable->GetRowMap())
	{
		FItemStructure* Item = (FItemStructure*)Row.Value;
		if (Item && Item->ItemID == ItemID) return Item;
	}
	return nullptr;
}

bool UInventoryComponent::CheckItem(int ItemID)
{
    FItemStructure* ItemData = GetItemData(ItemID);
    if (!ItemData) return false;

    for (FInventoryItemStructure& InvItem : InventoryItems)
    {
        if (InvItem.ItemID == ItemID)
        {
            return true;
        }
    }

    return false;
}


bool UInventoryComponent::AddItem(int ItemID, int Count)
{
    //개수가 0이하면 함수 취소
    if (Count <= 0) return false;
    UE_LOG(LogTemp, Log, TEXT("Item Count : %d"), Count);

    //아이템 정보 가져오기
    FItemStructure* ItemData = GetItemData(ItemID);
    if (!ItemData) return false;
    UE_LOG(LogTemp, Log, TEXT("Add Item ItemID : %d"), ItemID);

    //이미 있는 아이템 찾기
    int TempCount = Count;
    for (FInventoryItemStructure& InvItem : InventoryItems)
    {
        if (TempCount <= 0) return true;
        if (InvItem.ItemID == ItemID)
        {
            if (InvItem.Stack + TempCount > ItemData->MaxStack) //스택이 최대일 경우
            {
                TempCount -= ItemData->MaxStack - InvItem.Stack;
                InvItem.Stack += ItemData->MaxStack - InvItem.Stack;
                UE_LOG(LogTemp, Log, TEXT("Max Item Stack : %d"), InvItem.Stack);
                continue;
            }
            else //스택이 최대가 아닐 경우
            {
                InvItem.Stack += TempCount;
                UE_LOG(LogTemp, Log, TEXT("Now Item Stack : %d"), InvItem.Stack);
                ApplyInventory();
                return true;
            }
        }
    }

    // 새 아이템 추가
    while (TempCount > 0)
    {
        if (TempCount >= ItemData->MaxStack)
        {
            InventoryItems.Add(FInventoryItemStructure(ItemID, ItemData->MaxStack));
            TempCount -= ItemData->MaxStack;
            UE_LOG(LogTemp, Log, TEXT("Create Item, Now Item Stack : %d"), ItemData->MaxStack);
        }
        else
        {
            InventoryItems.Add(FInventoryItemStructure(ItemID, TempCount));
            TempCount = 0;
            UE_LOG(LogTemp, Log, TEXT("Create Item, Now Item Stack : %d"), TempCount);
        }
    }
    ApplyInventory();
    return true;
}

bool UInventoryComponent::RemoveItem(int ItemID, int Count)
{
    if (Count <= 0) return false;

    for (int32 i = 0; i < InventoryItems.Num(); ++i)
    {
        if (InventoryItems[i].ItemID == ItemID)
        {
            if (InventoryItems[i].Stack > Count)
            {
                InventoryItems[i].Stack -= Count;
            }
            else if (InventoryItems[i].Stack == Count)
            {
                InventoryItems.RemoveAt(i);
            }
            else
            {
                UE_LOG(LogTemp, Log, TEXT("Remove Fail : [%d - %d < 0]"), InventoryItems[i].Stack, Count);
                return false;
            }
            ApplyInventory();
            return true;
        }
    }
    return false; //아이템이 없는 경우
}

bool UInventoryComponent::UseItem(int ItemID)
{
    FInventoryItemStructure* InvItem = InventoryItems.FindByPredicate([ItemID](const FInventoryItemStructure& Item)
        {
            return Item.ItemID == ItemID;
        });

    if (!InvItem) return false;
    if (InvItem->Stack <= 0) return false;

    const FItemStructure* ItemData = GetItemData(ItemID);
    if (!ItemData) return false;

    UE_LOG(LogTemp, Log, TEXT("Use Item : %d"), ItemID);

    // 여기서 ItemType 별 처리
    switch (ItemData->ItemType)
    {
    case EItemType::Equipment:
        //장비템 사용 코드
        break;

    case EItemType::SkillBook:
        //스킬 북 사용 코드
        break;

    case EItemType::Consumable:
        UseConsumable(ItemID);
        RemoveItem(ItemID, 1);
        break;

    case EItemType::NonConsumable:
        //비사용 아이템 코드
        break;

    default:
        break;
    }

    ApplyInventory();
    return true;
}

void UInventoryComponent::ApplyInventory()
{
    if (PC && PC->InventoryUI)
    {
        if (PC->InventoryUI->IsInViewport())
        {
            PC->InventoryUI->InventorySeting();
            UE_LOG(LogTemp, Log, TEXT("Fast InventorySeting."));
        }
    }
}

void UInventoryComponent::UseConsumable(int ItemID)
{
    switch (ItemID)
    {
    case 10000:
        PC->HealHP(10);
        break;
    default:
        UE_LOG(LogTemp, Log, TEXT("ItemID %d is not existed."), ItemID);
        break;
    }
}