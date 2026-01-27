// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "InventoryComponent.h"
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
	UPROPERTY(BlueprintReadOnly, Category = "Player") UInventoryComponent* PlayerInventory;
	
	//체력바 설정 함수
	UFUNCTION(BlueprintCallable) void ChangeHPBar();
	//경험치바 설정 함수
	UFUNCTION(BlueprintCallable) void ChangeEXPBar();
	//레벨바 설정 함수
	UFUNCTION(BlueprintCallable) void ChangeLevelBar();
	//퀵슬롯바 설정 함수
	UFUNCTION(BlueprintCallable) void ChangeSlotBar();

	//스킬1 쿨타임 적용 UI
	void Skill1CooltimeUI(float Current, float Max);
	//스킬2 쿨타임 적용 UI
	void Skill2CooltimeUI(float Current, float Max);
	//스킬3 쿨타임 적용 UI
	void Skill3CooltimeUI(float Current, float Max);
	//스킬4 쿨타임 적용 UI
	void Skill4CooltimeUI(float Current, float Max);

	//슬롯1 쿨타임 적용 UI
	void Slot1CooltimeUI(float Current, float Max);
	//슬롯2 쿨타임 적용 UI
	void Slot2CooltimeUI(float Current, float Max);
	//슬롯3 쿨타임 적용 UI
	void Slot3CooltimeUI(float Current, float Max);
	//슬롯4 쿨타임 적용 UI
	void Slot4CooltimeUI(float Current, float Max);
	//슬롯5 쿨타임 적용 UI
	void Slot5CooltimeUI(float Current, float Max);

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
	UPROPERTY(meta = (BindWidget)) UTextBlock* LevelText;
	UPROPERTY(meta = (BindWidget)) UProgressBar* Skill1Progress;
	UPROPERTY(meta = (BindWidget)) UProgressBar* Skill2Progress;
	UPROPERTY(meta = (BindWidget)) UProgressBar* Skill3Progress;
	UPROPERTY(meta = (BindWidget)) UProgressBar* Skill4Progress;
	UPROPERTY(meta = (BindWidget)) UProgressBar* Slot1Progress;
	UPROPERTY(meta = (BindWidget)) UProgressBar* Slot2Progress;
	UPROPERTY(meta = (BindWidget)) UProgressBar* Slot3Progress;
	UPROPERTY(meta = (BindWidget)) UProgressBar* Slot4Progress;
	UPROPERTY(meta = (BindWidget)) UProgressBar* Slot5Progress;
	UPROPERTY(meta = (BindWidget)) UImage* Slot1Image;
	UPROPERTY(meta = (BindWidget)) UImage* Slot2Image;
	UPROPERTY(meta = (BindWidget)) UImage* Slot3Image;
	UPROPERTY(meta = (BindWidget)) UImage* Slot4Image;
	UPROPERTY(meta = (BindWidget)) UImage* Slot5Image;

	//머테리얼 인스턴스 접근 변수
	UMaterialInstanceDynamic* HPBarImageMT;
	UMaterialInstanceDynamic* EXPBarImageMT;

	//상호작용 함수
	UFUNCTION() void OptionButtonClick();
	UFUNCTION() void InventoryButtonClick();
	UFUNCTION() void SkillButtonClick();
};
