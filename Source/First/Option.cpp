// Fill out your copyright notice in the Description page of Project Settings.


#include "Option.h"
#include "Components/Button.h"
#include "MyCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MyGameInstance.h"

void UOption::NativeConstruct()
{
	Super::NativeConstruct();

	//초기값 설정
	UMyGameInstance* GI = Cast<UMyGameInstance>(GetGameInstance());
	if (GI)
	{
		MasterSlider->SetValue(GI->GIMasterVolume);
		BGMSlider->SetValue(GI->GIBGMVolume);
		SFXSlider->SetValue(GI->GISFXVolume);
	}

	//이벤트 할당
	CloseButton->OnClicked.AddDynamic(this, &UOption::CloseButtonClick);
	ExitButton->OnClicked.AddDynamic(this, &UOption::ExitButtonClick);
	MasterSlider->OnValueChanged.AddDynamic(this, &UOption::MasterSliderValueChanged);
	BGMSlider->OnValueChanged.AddDynamic(this, &UOption::BGMSliderValueChanged);
	SFXSlider->OnValueChanged.AddDynamic(this, &UOption::SFXSliderValueChanged);

	//오픈 애니메이션
	if (OpenAnim)
	{
		PlayAnimation(OpenAnim);
	}
}

void UOption::CloseButtonClick()
{
	UE_LOG(LogTemp, Log, TEXT("Clicked Close Button."));
	AMyCharacter* PCharacter = Cast<AMyCharacter>(GetOwningPlayerPawn());
	if (PCharacter)
	{
		UE_LOG(LogTemp, Log, TEXT("Cast Success."));
		PCharacter->ToggleOption();
	}
}

void UOption::ExitButtonClick()
{
	UE_LOG(LogTemp, Log, TEXT("Game Exit."));
	UKismetSystemLibrary::QuitGame(this, GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}

void UOption::MasterSliderValueChanged(float value)
{
	UMyGameInstance* GI = Cast<UMyGameInstance>(GetGameInstance());
	if (GI)
	{
		GI->GIMasterVolume = value;
		UE_LOG(LogTemp, Log, TEXT("Now Master Volume : %.2f"), value);
	}
}

void UOption::BGMSliderValueChanged(float value)
{
	UMyGameInstance* GI = Cast<UMyGameInstance>(GetGameInstance());
	if (GI)
	{
		GI->GIBGMVolume = value;
		UE_LOG(LogTemp, Log, TEXT("Now BGM Volume : %.2f"), value);
	}
}

void UOption::SFXSliderValueChanged(float value)
{
	UMyGameInstance* GI = Cast<UMyGameInstance>(GetGameInstance());
	if (GI)
	{
		GI->GISFXVolume = value;
		UE_LOG(LogTemp, Log, TEXT("Now SFX Volume : %.2f"), value);
	}
}
