// Fill out your copyright notice in the Description page of Project Settings.


#include "BowBase.h"

ABowBase::ABowBase()
{
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(Root);
}
