// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "InventoryItemStructure.generated.h"


USTRUCT(BlueprintType)
struct FIRST_API FInventoryItemStructure : public FTableRowBase
{
	GENERATED_BODY()
public:
	FInventoryItemStructure();
	FInventoryItemStructure(int ItemIDValue, int StackValue);
	//아이템 인덱스
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int ItemID;
	//아이템 개수
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int Stack;
};
