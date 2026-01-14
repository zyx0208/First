// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Option.generated.h"

/**
 * 
 */
UCLASS()
class FIRST_API UOption : public UUserWidget
{
	GENERATED_BODY()

protected:
	void NativeConstruct();

	//버튼 등록
	UPROPERTY(meta = (BindWidget)) UButton* CloseButton;
	UPROPERTY(meta = (BindWidget)) UButton* ExitButton;
	
	//버튼 상호작용 함수 등록
	UFUNCTION() void CloseButtonClick();
	UFUNCTION() void ExitButtonClick();

	//애니메이션
	UPROPERTY(meta = (BindWidgetAnim), Transient) UWidgetAnimation* OpenAnim;
};
