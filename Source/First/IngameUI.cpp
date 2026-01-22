// Fill out your copyright notice in the Description page of Project Settings.


#include "IngameUI.h"
#include "MyCharacter.h"

void UIngameUI::NativeConstruct()
{
	Super::NativeConstruct();

	//플레이어 불러오기
	PC = Cast<AMyCharacter>(GetOwningPlayerPawn());

	//이벤트 할당
	OptionButton->OnClicked.AddDynamic(this, &UIngameUI::OptionButtonClick);
	InventoryButton->OnClicked.AddDynamic(this, &UIngameUI::InventoryButtonClick);
	SkillButton->OnClicked.AddDynamic(this, &UIngameUI::SkillButtonClick);

	//머테리얼 접근
	if (HPBarImage)
	{
		//체력 머테리얼 가져오기
		UMaterialInterface* HPMaterial = Cast<UMaterialInterface>(HPBarImage->GetBrush().GetResourceObject());
		if (HPMaterial)
		{
			HPBarImageMT = UMaterialInstanceDynamic::Create(HPMaterial, this);
			HPBarImage->SetBrushFromMaterial(HPBarImageMT);
		}
		//경험치 머테리얼 가져오기
		UMaterialInterface* EXPMaterial = Cast<UMaterialInterface>(EXPBarImage->GetBrush().GetResourceObject());
		if (EXPMaterial)
		{
			EXPBarImageMT = UMaterialInstanceDynamic::Create(EXPMaterial, this);
			EXPBarImage->SetBrushFromMaterial(EXPBarImageMT);
		}
	}
	ChangeHPBar();
	ChangeEXPBar();
}

void UIngameUI::OptionButtonClick()
{
	if (PC) PC->ToggleOption();
}

void UIngameUI::InventoryButtonClick()
{
	if (PC) PC->ToggleInventory();
}

void UIngameUI::SkillButtonClick()
{
	if (PC) PC->ToggleSkill();
}

void UIngameUI::ChangeHPBar()
{
	if (PC)
	{
		//체력 머테리얼 파라미터 값 변경
		if (HPBarImageMT)
		{
			HPBarImageMT->SetScalarParameterValue(TEXT("Percentage"), PC->HPPercent());
		}
		
		//체력 수치값 표시
		if (PC->CurrentHP > 0)
		{
			FText HS = FText::FromString(FString::Printf(TEXT("%d  /  %d"), PC->CurrentHP, PC->MaxHP));
			HPBarText->SetText(HS);
		}
		else
		{
			FText HS = FText::FromString(FString::Printf(TEXT("Death"), PC->CurrentHP, PC->MaxHP));
			HPBarText->SetText(HS);
		}
	}
}

void UIngameUI::ChangeEXPBar()
{
	if (PC)
	{
		//경험치 머테리얼 파라미터 값 변경
		if (EXPBarImageMT)
		{
			EXPBarImageMT->SetScalarParameterValue(TEXT("Percentage"), PC->EXPPercent());
		}

		//체력 수치값 표시
		if (PC->EXP >= 0)
		{
			FText ES = FText::FromString(FString::Printf(TEXT("%.0f%%"), PC->EXPPercent() * 100.0f));
			EXPBarText->SetText(ES);
		}
		else
		{
			FText ES = FText::FromString(FString::Printf(TEXT("Error.")));
			EXPBarText->SetText(ES);
		}
	}
}

void UIngameUI::Skill1CooltimeUI(float Current, float Max)
{
	Skill1Progress->SetPercent(Current / Max);
}

void UIngameUI::Skill2CooltimeUI(float Current, float Max)
{
	Skill2Progress->SetPercent(Current / Max);
}

void UIngameUI::Skill3CooltimeUI(float Current, float Max)
{
	Skill3Progress->SetPercent(Current / Max);
}

void UIngameUI::Skill4CooltimeUI(float Current, float Max)
{
	Skill4Progress->SetPercent(Current / Max);
}