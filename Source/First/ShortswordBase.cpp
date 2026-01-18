// Fill out your copyright notice in the Description page of Project Settings.


#include "ShortswordBase.h"

AShortswordBase::AShortswordBase()
{
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(Root);
}