// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "TooltipUI.h"
#include "ItemStructure.h"
#include "ItemOptionUI.h"
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
	UFUNCTION(BlueprintCallable) void SetItemInfo(int ItemIDValue, int CountValue, UTexture2D* IconValue, FName& NameValue, FString& DescriptionValue, EItemType ItemTypeValue);
    
    //툴팁 클래스
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI") TSubclassOf<UTooltipUI> TooltipClass;
    UTooltipUI* Tooltip;

    //아이템 옵션 클래스
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI") TSubclassOf<UItemOptionUI> ItemOptionUIClass;
    UItemOptionUI* ItemOptionUI;

    //UI 제거 시 실행(툴팁 삭제를 위함)
    virtual void NativeDestruct() override;

protected:
    //이미지
    UPROPERTY(meta = (BindWidget)) UImage* ItemIconImage;
    //개수 표시 텍스트 박스
    UPROPERTY(meta = (BindWidget)) UTextBlock* CountText;
    //아이템 이름 박스
    UPROPERTY(meta = (BindWidget)) UTextBlock* NameText;

    //아이템 이름
    UPROPERTY() FName ItemName;
    //아이템 인덱스
    UPROPERTY() int ItemID;
    //아이템 개수
    UPROPERTY() int Count;
    //아이템 설명
    UPROPERTY() FString Description;
    //아이템 타입
    UPROPERTY() EItemType ItemType;
   
    //툴팁 생성
    virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
    //툴팁 제거
    virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
    //아이템 옵션 생성
    virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
};
