// Fill out your copyright notice in the Description page of Project Settings.


#include "Option.h"
#include "Components/Button.h"
#include "MyCharacter.h"
#include "Kismet/KismetSystemLibrary.h"

void UOption::NativeConstruct()
{
	Super::NativeConstruct();

	//기능 위젯 할당
	CloseButton = Cast<UButton>(GetWidgetFromName(TEXT("CloseOptionButton")));
	ExitButton = Cast<UButton>(GetWidgetFromName(TEXT("ExitButton")));

	//버튼 이벤트 할당
	CloseButton->OnClicked.AddDynamic(this, &UOption::CloseButtonClick);
	ExitButton->OnClicked.AddDynamic(this, &UOption::ExitButtonClick);
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
	UKismetSystemLibrary::QuitGame(this, GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}