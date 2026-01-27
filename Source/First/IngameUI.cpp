// Fill out your copyright notice in the Description page of Project Settings.


#include "IngameUI.h"
#include "MyCharacter.h"
#include "ItemStructure.h"


void UIngameUI::NativeConstruct()
{
	Super::NativeConstruct();

	//플레이어 불러오기
	PC = Cast<AMyCharacter>(GetOwningPlayerPawn());
	if (PC)
	{
		PlayerInventory = PC->CharacterInventory;
	}

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
	ChangeLevelBar();
	ChangeSlotBar();
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

void UIngameUI::ChangeLevelBar()
{
	if (PC)
	{
		//레벨 수치 변경
		FText LS = FText::FromString(FString::Printf(TEXT("LV. %d"), PC->Level));
		LevelText->SetText(LS);
	}
}

void UIngameUI::ChangeSlotBar()
{
	UE_LOG(LogTemp, Log, TEXT("Change Slot Bar."));
	if (PC->Slot[0])
	{
		FItemStructure* ItemData = PlayerInventory->GetItemData(PC->Slot[0]);
		if (ItemData)
		{
			FSlateBrush Brush = Slot1Image->Brush;
			Brush.SetResourceObject(ItemData->ItemIcon);
			Brush.ImageSize = FVector2D(ItemData->ItemIcon->GetSizeX(), ItemData->ItemIcon->GetSizeY());
			Brush.DrawAs = ESlateBrushDrawType::Image;

			Slot1Image->SetBrush(Brush);
			UE_LOG(LogTemp, Log, TEXT("Seting Slot 1"));
		}
	}
	else
	{
		FSlateBrush Brush = Slot1Image->Brush;
		Brush.DrawAs = ESlateBrushDrawType::NoDrawType;
		Brush.SetResourceObject(nullptr);
		Slot1Image->SetBrush(Brush);
	}
	if (PC->Slot[1])
	{
		FItemStructure* ItemData = PlayerInventory->GetItemData(PC->Slot[1]);
		if (ItemData)
		{
			FSlateBrush Brush = Slot2Image->Brush;
			Brush.SetResourceObject(ItemData->ItemIcon);
			Brush.ImageSize = FVector2D(ItemData->ItemIcon->GetSizeX(), ItemData->ItemIcon->GetSizeY());
			Brush.DrawAs = ESlateBrushDrawType::Image;

			Slot2Image->SetBrush(Brush);
			UE_LOG(LogTemp, Log, TEXT("Seting Slot 2"));
		}
	}
	else
	{
		FSlateBrush Brush = Slot2Image->Brush;
		Brush.DrawAs = ESlateBrushDrawType::NoDrawType;
		Brush.SetResourceObject(nullptr);
		Slot2Image->SetBrush(Brush);
	}
	if (PC->Slot[2])
	{
		FItemStructure* ItemData = PlayerInventory->GetItemData(PC->Slot[2]);
		if (ItemData)
		{
			FSlateBrush Brush = Slot3Image->Brush;
			Brush.SetResourceObject(ItemData->ItemIcon);
			Brush.ImageSize = FVector2D(ItemData->ItemIcon->GetSizeX(), ItemData->ItemIcon->GetSizeY());
			Brush.DrawAs = ESlateBrushDrawType::Image;

			Slot3Image->SetBrush(Brush);
			UE_LOG(LogTemp, Log, TEXT("Seting Slot 3"));
		}
	}
	else
	{
		FSlateBrush Brush = Slot3Image->Brush;
		Brush.DrawAs = ESlateBrushDrawType::NoDrawType;
		Brush.SetResourceObject(nullptr);
		Slot3Image->SetBrush(Brush);
	}
	if (PC->Slot[3])
	{
		FItemStructure* ItemData = PlayerInventory->GetItemData(PC->Slot[3]);
		if (ItemData)
		{
			FSlateBrush Brush = Slot4Image->Brush;
			Brush.SetResourceObject(ItemData->ItemIcon);
			Brush.ImageSize = FVector2D(ItemData->ItemIcon->GetSizeX(), ItemData->ItemIcon->GetSizeY());
			Brush.DrawAs = ESlateBrushDrawType::Image;

			Slot4Image->SetBrush(Brush);
			UE_LOG(LogTemp, Log, TEXT("Seting Slot 4"));
		}
	}
	else
	{
		FSlateBrush Brush = Slot4Image->Brush;
		Brush.DrawAs = ESlateBrushDrawType::NoDrawType;
		Brush.SetResourceObject(nullptr);
		Slot4Image->SetBrush(Brush);
	}
	if (PC->Slot[4])
	{
		FItemStructure* ItemData = PlayerInventory->GetItemData(PC->Slot[4]);
		if (ItemData)
		{
			FSlateBrush Brush = Slot5Image->Brush;
			Brush.SetResourceObject(ItemData->ItemIcon);
			Brush.ImageSize = FVector2D(ItemData->ItemIcon->GetSizeX(), ItemData->ItemIcon->GetSizeY());
			Brush.DrawAs = ESlateBrushDrawType::Image;

			Slot5Image->SetBrush(Brush);
			UE_LOG(LogTemp, Log, TEXT("Seting Slot 5"));
		}
	}
	else
	{
		FSlateBrush Brush = Slot5Image->Brush;
		Brush.DrawAs = ESlateBrushDrawType::NoDrawType;
		Brush.SetResourceObject(nullptr);
		Slot5Image->SetBrush(Brush);
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

void UIngameUI::Slot1CooltimeUI(float Current, float Max)
{
	Slot1Progress->SetPercent(Current / Max);
}

void UIngameUI::Slot2CooltimeUI(float Current, float Max)
{
	Slot2Progress->SetPercent(Current / Max);
}

void UIngameUI::Slot3CooltimeUI(float Current, float Max)
{
	Slot3Progress->SetPercent(Current / Max);
}

void UIngameUI::Slot4CooltimeUI(float Current, float Max)
{
	Slot4Progress->SetPercent(Current / Max);
}

void UIngameUI::Slot5CooltimeUI(float Current, float Max)
{
	Slot5Progress->SetPercent(Current / Max);
}