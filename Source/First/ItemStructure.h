// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemStructure.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Equipment, SkillBook, Consumable, NonConsumable
};

USTRUCT(BlueprintType)
struct FIRST_API FItemStructure : public FTableRowBase
{
    GENERATED_BODY()

public:
    //아이템 인덱스
    UPROPERTY(EditAnywhere, BlueprintReadOnly) int ItemID;
    //아이템 이름
    UPROPERTY(EditAnywhere, BlueprintReadOnly) FName ItemName;
    //아이템 타입[Equipment, SkillBook, Consumable, NonConsumable]
    UPROPERTY(EditAnywhere, BlueprintReadOnly) EItemType ItemType;
    //아이템 이미지
    UPROPERTY(EditAnywhere, BlueprintReadOnly) UTexture2D* ItemIcon;
    //최대 스택 개수
    UPROPERTY(EditAnywhere, BlueprintReadOnly) int MaxStack;
    //아이템 설명
    UPROPERTY(EditAnywhere, BlueprintReadOnly) FString Description;
};
