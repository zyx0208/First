// Fill out your copyright notice in the Description page of Project Settings.


#include "KnightWeapon.h"

AKnightWeapon::AKnightWeapon()
{
    WSHP = 3;
    WSAttackDamage = 3;
    WSCooldown = 2;
}

void AKnightWeapon::SetupSkills()
{
    //배열 초기화
    AllSkills.Empty();

    //공용 스킬 먼저 등록
    Super::SetupSkills();

    //무사 전용 스킬 등록
    AllSkills.Add(FSkillDelegate::CreateUObject(this, &AKnightWeapon::ShieldBash));
}

void AKnightWeapon::ShieldBash()
{
    UE_LOG(LogTemp, Log, TEXT("Knight ShieldBash executed!"));


}
