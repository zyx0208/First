// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "IngameUI.generated.h"

//양쪽에서의 참조 때문에 전방 선언
class AMyCharacter;

UCLASS()
class FIRST_API UIngameUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//플레이어 정보 불러오기
	UPROPERTY(BlueprintReadOnly, Category = "Player") AMyCharacter* PC;
	// 플레이어 설정 함수
	UFUNCTION(BlueprintCallable) void SetPlayer(AMyCharacter* Player);

protected:
	void NativeConstruct();

	//위젯
	UPROPERTY(meta = (BindWidget)) UButton* OptionButton;
	UPROPERTY(meta = (BindWidget)) UButton* InventoryButton;
	UPROPERTY(meta = (BindWidget)) UButton* SkillButton;

	//상호작용 함수
	UFUNCTION() void OptionButtonClick();
	UFUNCTION() void InventoryButtonClick();
	UFUNCTION() void SkillButtonClick();
};
