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
	// Sets default values for this character's properties
	AMyCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//옵션UI함수
	void ToggleOption();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//이동 설정
	void MoveForward(float value);
	void MoveRight(float value);

	//이동속도
	float MoveSpeed;

	//달리기
	void StartRun();
	void StopRun();

	//달리기 여부
	bool IsRun;

	//시점 설정
	void Turn(float value);
	void LookUp(float value);
	
	//옵션UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI") TSubclassOf<UUserWidget> OptionUIClass;
	UUserWidget* OptionUI;

	//점프함수
	void StartJump();
};
