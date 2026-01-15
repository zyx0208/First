// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Slider.h"
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

	//위젯
	UPROPERTY(meta = (BindWidget)) UButton* CloseButton;
	UPROPERTY(meta = (BindWidget)) UButton* ExitButton;
	UPROPERTY(meta = (BindWidget)) USlider* MasterSlider;
	UPROPERTY(meta = (BindWidget)) USlider* BGMSlider;
	UPROPERTY(meta = (BindWidget)) USlider* SFXSlider;

	//상호작용 함수
	UFUNCTION() void CloseButtonClick();
	UFUNCTION() void ExitButtonClick();
	UFUNCTION() void MasterSliderValueChanged(float value);
	UFUNCTION() void BGMSliderValueChanged(float value);
	UFUNCTION() void SFXSliderValueChanged(float value);
	

	//애니메이션
	UPROPERTY(meta = (BindWidgetAnim), Transient) UWidgetAnimation* OpenAnim;
};
