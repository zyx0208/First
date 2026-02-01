// Fill out your copyright notice in the Description page of Project Settings.


#include "ChangeWeapon.h"
#include "MyCharacter.h"


void UChangeWeapon::NativeConstruct()
{
	Super::NativeConstruct();

	CloseButton->OnClicked.AddDynamic(this, &UChangeWeapon::CloseButtonClick);
	ChangeWeaponButton1->OnClicked.AddDynamic(this, &UChangeWeapon::SelectShopButton1Click);
	ChangeWeaponButton2->OnClicked.AddDynamic(this, &UChangeWeapon::SelectShopButton2Click);

	AWeaponBase* WeaponBase = Player->Weapon;
	if (Cast<AKnightWeapon>(WeaponBase))
	{
		UE_LOG(LogTemp, Log, TEXT("Now Weapon : 1"));
		Preset = 1;
		ChangeWeaponButton1->SetIsEnabled(false);
		ChangeWeaponButton2->SetIsEnabled(true);
	}
	else if (Cast<AGuardianWeapon>(WeaponBase))
	{
		UE_LOG(LogTemp, Log, TEXT("Now Weapon : 2"));
		Preset = 1;
		ChangeWeaponButton1->SetIsEnabled(true);
		ChangeWeaponButton2->SetIsEnabled(false);
	}
	else if (Cast<ALongbowWeapon>(WeaponBase))
	{
		UE_LOG(LogTemp, Log, TEXT("Now Weapon : 3"));
		Preset = 2;
		ChangeWeaponButton1->SetIsEnabled(false);
		ChangeWeaponButton2->SetIsEnabled(true);
	}
	else if (Cast<AShortbowWeapon>(WeaponBase))
	{
		UE_LOG(LogTemp, Log, TEXT("Now Weapon : 4"));
		Preset = 2;
		ChangeWeaponButton1->SetIsEnabled(true);
		ChangeWeaponButton2->SetIsEnabled(false);
	}
	else if (Cast<AMageWeapon>(WeaponBase))
	{
		UE_LOG(LogTemp, Log, TEXT("Now Weapon : 5"));
		Preset = 3;
		ChangeWeaponButton1->SetIsEnabled(false);
		ChangeWeaponButton2->SetIsEnabled(true);
	}
	else if (Cast<AWhitemageWeapon>(WeaponBase))
	{
		UE_LOG(LogTemp, Log, TEXT("Now Weapon : 6"));
		Preset = 3;
		ChangeWeaponButton1->SetIsEnabled(true);
		ChangeWeaponButton2->SetIsEnabled(false);
	}
	else if (Cast<AAssassinWeapon>(WeaponBase))
	{
		UE_LOG(LogTemp, Log, TEXT("Now Weapon : 7"));
		Preset = 4;
		ChangeWeaponButton1->SetIsEnabled(false);
		ChangeWeaponButton2->SetIsEnabled(true);
	}
	else if (Cast<AThrowerWeapon>(WeaponBase))
	{
		UE_LOG(LogTemp, Log, TEXT("Now Weapon : 8"));
		Preset = 4;
		ChangeWeaponButton1->SetIsEnabled(true);
		ChangeWeaponButton2->SetIsEnabled(false);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Now Weapon : X"));
		Preset = 0;
		ChangeWeaponButton1->SetIsEnabled(false);
		ChangeWeaponButton2->SetIsEnabled(false);
	}

	switch (Preset)
	{
	case 1:
		ChangeWeaponButton1Text->SetText(FText::FromString(FString::Printf(TEXT("무사"))));
		ChangeWeaponButton2Text->SetText(FText::FromString(FString::Printf(TEXT("수호자"))));
		break;
	case 2:
		ChangeWeaponButton1Text->SetText(FText::FromString(FString::Printf(TEXT("장궁"))));
		ChangeWeaponButton2Text->SetText(FText::FromString(FString::Printf(TEXT("단궁"))));
		break;
	case 3:
		ChangeWeaponButton1Text->SetText(FText::FromString(FString::Printf(TEXT("마법사"))));
		ChangeWeaponButton2Text->SetText(FText::FromString(FString::Printf(TEXT("백마법사"))));
		break;
	case 4:
		ChangeWeaponButton1Text->SetText(FText::FromString(FString::Printf(TEXT("암살자"))));
		ChangeWeaponButton2Text->SetText(FText::FromString(FString::Printf(TEXT("투척수"))));
		break;
	default:
		ChangeWeaponButton1Text->SetText(FText::FromString(FString::Printf(TEXT("변경 불가"))));
		ChangeWeaponButton2Text->SetText(FText::FromString(FString::Printf(TEXT("변경 불가"))));
		break;
	}
}

void UChangeWeapon::CloseButtonClick()
{
	UE_LOG(LogTemp, Log, TEXT("Clicked Close Button."));
	if (Player)
	{
		UE_LOG(LogTemp, Log, TEXT("Cast Success."));
		Player->PController->SetShowMouseCursor(false);
		Player->PController->SetInputMode(FInputModeGameOnly());
		RemoveFromParent();
	}
}

void UChangeWeapon::SelectShopButton1Click()
{
	switch (Preset)
	{
	case 1:
		Player->WeaponAttach(Weapon1);
		UE_LOG(LogTemp, Log, TEXT("Change To Weapon1."));
		break;
	case 2:
		Player->WeaponAttach(Weapon3);
		UE_LOG(LogTemp, Log, TEXT("Change To Weapon3."));
		break;
	case 3:
		Player->WeaponAttach(Weapon5);
		UE_LOG(LogTemp, Log, TEXT("Change To Weapon5."));
		break;
	case 4:
		Player->WeaponAttach(Weapon7);
		UE_LOG(LogTemp, Log, TEXT("Change To Weapon7."));
		break;
	default:
		break;
	}
	CloseButtonClick();
}

void UChangeWeapon::SelectShopButton2Click()
{
	switch (Preset)
	{
	case 1:
		Player->WeaponAttach(Weapon2);
		UE_LOG(LogTemp, Log, TEXT("Change To Weapon2."));
		break;
	case 2:
		Player->WeaponAttach(Weapon4);
		UE_LOG(LogTemp, Log, TEXT("Change To Weapon4."));
		break;
	case 3:
		Player->WeaponAttach(Weapon6);
		UE_LOG(LogTemp, Log, TEXT("Change To Weapon6."));
		break;
	case 4:
		Player->WeaponAttach(Weapon8);
		UE_LOG(LogTemp, Log, TEXT("Change To Weapon8."));
		break;
	default:
		break;
	}
	CloseButtonClick();
}