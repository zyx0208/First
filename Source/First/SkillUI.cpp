// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillUI.h"

void USkillUI::NativeConstruct()
{
	Super::NativeConstruct();

	//이벤트 할당
	CloseButton->OnClicked.AddDynamic(this, &USkillUI::CloseButtonClick);
}

void USkillUI::CloseButtonClick()
{
	UE_LOG(LogTemp, Log, TEXT("Clicked Close Button."));
	AMyCharacter* PCharacter = Cast<AMyCharacter>(GetOwningPlayerPawn());
	if (PCharacter)
	{
		UE_LOG(LogTemp, Log, TEXT("Cast Success."));
		PCharacter->ToggleSkill();
	}
}