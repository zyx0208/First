// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class FIRST_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMyCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//옵션UI함수
	void ToggleOption();

protected:
	virtual void BeginPlay() override;

	//이동 설정
	void MoveForward(float value);
	void MoveRight(float value);

	//이동속도
	float MoveSpeed;

	//이동 여부
	UPROPERTY(BlueprintReadOnly) bool IsWalk;

	//달리기
	void StartRun();
	void StopRun();

	//달리기 여부
	UPROPERTY(BlueprintReadOnly) bool IsRun;

	//시점 설정
	void Turn(float value);
	void LookUp(float value);
	
	//옵션UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI") TSubclassOf<UUserWidget> OptionUIClass;
	UUserWidget* OptionUI;

	//UI모드를 확인하는 변수
	bool IsUIMode;

	//점프함수
	void StartJump();

	//크로스헤어UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI") TSubclassOf<UUserWidget> CrosshairUIClass;
	UUserWidget* CrosshairUI;

	//크로스헤어UI 생성함수
	void ToggleCrosshair();
};
