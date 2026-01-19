// Fill out your copyright notice in the Description page of Project Settings.


#include "LongswordBase.h"

ALongswordBase::ALongswordBase()
{
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(Root);
}

void ALongswordBase::SetupSkills()
{
    //배열 초기화
    AllSkills.Empty();
    
    //공용 스킬 먼저 등록
    Super::SetupSkills();

    //장검 공용 스킬 등록
    AllSkills.Add(FSkillDelegate::CreateUObject(this, &ALongswordBase::HorizontalSlash));
}

void ALongswordBase::HorizontalSlash()
{
    //지연 생성
    AWeaponAttack* Attack = GetWorld()->SpawnActorDeferred<AWeaponAttack>(AWeaponAttack::StaticClass(), FTransform::Identity);

    if (!Attack) return;

    //공격 범위 붙이기
    Attack->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
    //공격 위치 설정
    Attack->SetActorRelativeLocation(FVector(0.0f, 0.0f, 50.0f));
    Attack->SetActorRelativeRotation(FRotator::ZeroRotator);
    //매개변수 주입
    Attack->Damage = 30.f * AttackDamageRate;
    Attack->Radius = 20.f;
    Attack->LifeTime = 10.0f;

    //생성 완료
    Attack->FinishSpawning(FTransform::Identity);

    //검 움직임

    UE_LOG(LogTemp, Log, TEXT("LongSword HorizontalSlash executed!"));
}