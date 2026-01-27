// Fill out your copyright notice in the Description page of Project Settings.


#include "MageBase.h"

AMageBase::AMageBase()
{
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(Root);
}
