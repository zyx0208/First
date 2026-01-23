// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

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
    for (FInventoryItemStructure& InvItem : InventoryItems)
    {
        if (InvItem.ItemID == ItemID)
        {
            //스택 가능 아이템
            if (ItemData->MaxStack > 1)
            {
                InvItem.Stack += Count;
                UE_LOG(LogTemp, Log, TEXT("Now Item Stack : %d"), InvItem.Stack);
                return true;
            }
            break;
        }
    }

    // 새 아이템 추가
    FInventoryItemStructure NewItem(ItemID, Count);
    InventoryItems.Add(NewItem);
    UE_LOG(LogTemp, Log, TEXT("Create Item, Now Item Stack : %d"), Count);
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
            else //개수가 0이하면 제거
            {
                InventoryItems.RemoveAt(i);
            }
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

    const FItemStructure* ItemData = GetItemData(ItemID);
    if (!ItemData) return false;

    // 여기서 ItemType 별 처리
    switch (ItemData->ItemType)
    {
    case EItemType::Equipment:
        //장비 아이템 사용 코드
        break;

    case EItemType::SkillBook:
        //스킬 북 사용 코드
        break;

    case EItemType::Consumable:
        //사용 아이템 코드
        break;

    case EItemType::NonConsumable:
        //비사용 아이템 코드
        break;

    default:
        break;
    }

    //임시용 사용 후 수량 감소
    RemoveItem(ItemID, 1);

    return true;
}