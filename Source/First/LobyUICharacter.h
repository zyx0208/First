// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LobyUICharacter.generated.h"

UCLASS()
class FIRST_API ALobyUICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ALobyUICharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

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

	//점프함수
	void StartJump();

};