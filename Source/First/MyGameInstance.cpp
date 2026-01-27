// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "MySaveGame.h"
#include "Kismet/GameplayStatics.h"

void UMyGameInstance::Init()
{
    Super::Init();
    LoadAudioSettings();
}

void UMyGameInstance::Shutdown()
{
    SaveAudioSettings();
    Super::Shutdown();
}

void UMyGameInstance::LoadAudioSettings()
{
    if (UMySaveGame* SaveData = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot("SaveData", 0)))
    {
        GIMasterVolume = SaveData->MasterVolume;
        GIBGMVolume = SaveData->BGMVolume;
        GISFXVolume = SaveData->SFXVolume;
    }
    else
    {
        //저장된 파일이 없으면 1.0f로 고정
        GIMasterVolume = 1.0f;
        GIBGMVolume = 1.0f;
        GISFXVolume = 1.0f;
    }
}

void UMyGameInstance::SaveAudioSettings()
{
    UMySaveGame* SaveData = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));

    SaveData->MasterVolume = GIMasterVolume;
    SaveData->BGMVolume = GIBGMVolume;
    SaveData->SFXVolume = GISFXVolume;

    UGameplayStatics::SaveGameToSlot(SaveData, "SaveData", 0);
}
