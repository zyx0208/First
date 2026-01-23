// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryItemStructure.h"
#include "ItemStructure.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIRST_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//아이템 데이터테이블
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI") UDataTable* ItemDataTable;

	//아이템 데이터테이블에서 정보를 가져오는 함수
	FItemStructure* GetItemData(int ItemID);

	//인벤토리 배열
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TArray<FInventoryItemStructure> InventoryItems;

	//아이템 추가 함수
	UFUNCTION(BlueprintCallable) bool AddItem(int ItemID, int Count);

	//아이템 제거
	UFUNCTION(BlueprintCallable) bool RemoveItem(int ItemID, int Count);

	//아이템 사용
	UFUNCTION(BlueprintCallable)bool UseItem(int ItemID);


};
