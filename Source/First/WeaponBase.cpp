// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
    IsAttacking = false;
    SetupSkills();
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeaponBase::SetupSkills()
{
    //배열 초기화
    AllSkills.Empty();

    //공용 스킬이 생기면 추가할 예정
}

void AWeaponBase::UseSkill(int Slot)
{
    if (AllSkills.IsValidIndex(Slot))
    {
        AllSkills[Slot].ExecuteIfBound();
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("%d Skill is not existed."), Slot);
    }
}
