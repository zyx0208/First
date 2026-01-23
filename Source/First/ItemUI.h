// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "ItemUI.generated.h"

/**
 * 
 */
UCLASS()
class FIRST_API UItemUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//아이템 정보 세팅[아이템ID, 개수, 아이콘, 표시이름, 설명]
	UFUNCTION(BlueprintCallable) void SetItemInfo(int ItemIDValue, int CountValue, UTexture2D* IconValue, FName& NameValue, FString& DescriptionValue);

protected:
    //이미지
    UPROPERTY(meta = (BindWidget)) UImage* ItemIconImage;
    //개수 표시 텍스트
    UPROPERTY(meta = (BindWidget)) UTextBlock* CountText;
    //아이템 이름
    UPROPERTY(meta = (BindWidget)) UTextBlock* NameText;
    //아이템 인덱스
    UPROPERTY() int ItemID;
    //아이템 개수
    UPROPERTY() int Count;
    //아이템 설명
    UPROPERTY() FString Description;
};
