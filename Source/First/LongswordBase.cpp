// Fill out your copyright notice in the Description page of Project Settings.


#include "LongswordBase.h"

ALongswordBase::ALongswordBase()
{
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(Root);
}