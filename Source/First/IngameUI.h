// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Materials/MaterialInstanceDynamic.h"
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
	
	//체력바 설정 함수
	UFUNCTION(BlueprintCallable) void ChangeHPBar();
	//경험치바 설정 함수
	UFUNCTION(BlueprintCallable) void ChangeEXPBar();

	//스킬1 쿨타임 적용 UI
	void Skill1CooltimeUI(float Current, float Max);
	//스킬2 쿨타임 적용 UI
	void Skill2CooltimeUI(float Current, float Max);
	//스킬3 쿨타임 적용 UI
	void Skill3CooltimeUI(float Current, float Max);
	//스킬4 쿨타임 적용 UI
	void Skill4CooltimeUI(float Current, float Max);

protected:
	void NativeConstruct();

	//위젯
	UPROPERTY(meta = (BindWidget)) UButton* OptionButton;
	UPROPERTY(meta = (BindWidget)) UButton* InventoryButton;
	UPROPERTY(meta = (BindWidget)) UButton* SkillButton;
	UPROPERTY(meta = (BindWidget)) UImage* HPBarImage;
	UPROPERTY(meta = (BindWidget)) UImage* EXPBarImage;
	UPROPERTY(meta = (BindWidget)) UTextBlock* HPBarText;
	UPROPERTY(meta = (BindWidget)) UTextBlock* EXPBarText;
	UPROPERTY(meta = (BindWidget)) UProgressBar* Skill1Progress;
	UPROPERTY(meta = (BindWidget)) UProgressBar* Skill2Progress;
	UPROPERTY(meta = (BindWidget)) UProgressBar* Skill3Progress;
	UPROPERTY(meta = (BindWidget)) UProgressBar* Skill4Progress;

	//머테리얼 인스턴스 접근 변수
	UMaterialInstanceDynamic* HPBarImageMT;
	UMaterialInstanceDynamic* EXPBarImageMT;

	//상호작용 함수
	UFUNCTION() void OptionButtonClick();
	UFUNCTION() void InventoryButtonClick();
	UFUNCTION() void SkillButtonClick();
};
