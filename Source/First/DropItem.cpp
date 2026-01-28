// Fill out your copyright notice in the Description page of Project Settings.


#include "DropItem.h"
#include "MyCharacter.h"
#include "InventoryComponent.h"

ADropItem::ADropItem()
{
	PrimaryActorTick.bCanEverTick = true;
	ItemID = 10000;
	Count = 1;
	SetingDropItem();
}

ADropItem::ADropItem(int ItemIDValue, int CountValue)
{
	PrimaryActorTick.bCanEverTick = true;
	ItemID = ItemIDValue;
	Count = CountValue;
	SetingDropItem();
}

void ADropItem::SetingDropItem()
{
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->InitSphereRadius(50.f);
	Collision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Collision->SetCollisionObjectType(ECC_GameTraceChannel2);
	Collision->SetCollisionResponseToAllChannels(ECR_Ignore);
	Collision->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	Collision->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	Collision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	Collision->SetSimulatePhysics(true);
	Collision->SetEnableGravity(true);
	Collision->BodyInstance.bLockXRotation = true;
	Collision->BodyInstance.bLockYRotation = true;
	Collision->BodyInstance.bLockZRotation = true;
	SetRootComponent(Collision);

	ItemPlane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemPlane"));
	ItemPlane->SetupAttachment(Collision);
}

FItemStructure* ADropItem::SetingItemInfo(int ItemIDValue)
{
	//데이터베이스가 없을 경우 null 반환
	if (!ItemDataTable) return nullptr;

	//ItemID로 DataTable 전체 순회
	for (auto& Row : ItemDataTable->GetRowMap())
	{
		FItemStructure* Item = (FItemStructure*)Row.Value;
		if (Item && Item->ItemID == ItemIDValue) return Item;
	}
	return nullptr;
}

void ADropItem::BeginPlay()
{
	Super::BeginPlay();

	//아이템 표시
	if (ItemMaterial && ItemPlane)
	{
		ItemMaterialInstance = UMaterialInstanceDynamic::Create(ItemMaterial, this);
		ItemPlane->SetMaterial(0, ItemMaterialInstance);
		FItemStructure* item = SetingItemInfo(ItemID);
		if (item && ItemMaterialInstance)
		{
			ItemMaterialInstance->SetTextureParameterValue(TEXT("SetIcon"), item->ItemIcon);
			UE_LOG(LogTemp, Log, TEXT("Set Image."));
		}
	}

	if (Collision)
	{
		Collision->OnComponentBeginOverlap.AddDynamic(this, &ADropItem::OnOverlap);
	}
}

void ADropItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//아이템 회전 효과
	FRotator Rt = ItemPlane->GetRelativeRotation();
	Rt.Yaw += DeltaTime * 90.f;
	ItemPlane->SetRelativeRotation(Rt);
}

void ADropItem::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("Overlap!"));

	if (!OtherActor) return;

	AMyCharacter* Player = Cast<AMyCharacter>(OtherActor);
	if (Player)
	{
		Player->CharacterInventory->AddItem(ItemID, Count);
		Destroy();
	}
}