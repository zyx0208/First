// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class FIRST_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
    //게임이 켜지는 순간
    virtual void Init() override;
    //게임이 꺼지는 순간
    virtual void Shutdown() override;

    //오디오 설정 불러오기
    void LoadAudioSettings();
    //오디오 설정 저장
    void SaveAudioSettings();

    //마스터 볼륨(게임인스턴스 용)
    UPROPERTY(BlueprintReadWrite) float GIMasterVolume;
    //배경음악 볼륨(게임인스턴스 용)
    UPROPERTY(BlueprintReadWrite) float GIBGMVolume;
    //효과음 볼륨(게임인스턴스 용)
    UPROPERTY(BlueprintReadWrite) float GISFXVolume;
};
