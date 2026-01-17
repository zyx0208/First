// Fill out your copyright notice in the Description page of Project Settings.


#include "LobyUICharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ALobyUICharacter::ALobyUICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALobyUICharacter::BeginPlay()
{
	Super::BeginPlay();
	
	//초기 설정
	MoveSpeed = GetCharacterMovement()->MaxWalkSpeed;
	IsRun = false;
	IsWalk = false;
	bUseControllerRotationYaw = false;

	//마우스 보이게 + 마우스로만 메뉴 선택
	APlayerController* PController = Cast<APlayerController>(GetController());
	PController->bShowMouseCursor = true;
	PController->SetInputMode(FInputModeGameOnly());
}

// Called every frame
void ALobyUICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//움직임 판단
	IsWalk = !FMath::IsNearlyZero(GetInputAxisValue("MoveForward")) || !FMath::IsNearlyZero(GetInputAxisValue("MoveRight"));

	//캐릭터 방향 설정
	if (IsWalk)
	{
		FVector MoveDirection = FVector(GetInputAxisValue("MoveForward"), GetInputAxisValue("MoveRight"), 0.0f);
		if (!MoveDirection.IsNearlyZero())
		{
			MoveDirection.Normalize();
			FRotator PR = MoveDirection.Rotation();

			// 캐릭터 회전 적용
			SetActorRotation(PR);
		}
	}
}

// Called to bind functionality to input
void ALobyUICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//이동
	PlayerInputComponent->BindAxis("MoveForward", this, &ALobyUICharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ALobyUICharacter::MoveRight);

	//달리기
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ALobyUICharacter::StartRun);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ALobyUICharacter::StopRun);

	//점프
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ALobyUICharacter::Jump);
}

void ALobyUICharacter::MoveForward(float value)
{
	//이동
	if ((Controller) && (value != 0.0f))
	{
		AddMovementInput(FVector(1.0f, 0.0f, 0.0f), value);
	}
}

void ALobyUICharacter::MoveRight(float value)
{
	//이동
	if ((Controller) && (value != 0.0f))
	{
		AddMovementInput(FVector(0.0f, 1.0f, 0.0f), value);
	}
}

void ALobyUICharacter::StartRun()
{
	IsRun = true;
	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed * 2.0f;
}

void ALobyUICharacter::StopRun()
{
	IsRun = false;
	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
}

void ALobyUICharacter::StartJump()
{
	Jump();
}