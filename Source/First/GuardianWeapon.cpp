// Fill out your copyright notice in the Description page of Project Settings.


#include "GuardianWeapon.h"

AGuardianWeapon::AGuardianWeapon()
{
	WSHP = 5;
	WSAttackDamage = 1;
	WSCooldown = 2;
}

void AGuardianWeapon::SetupSkills()
{
    //배열 초기화
    AllSkills.Empty();

    //공용 스킬 먼저 등록
    Super::SetupSkills();

    //수호자 전용 스킬 등록
    //AllSkills.Add(FSkillDelegate::CreateUObject(this, &AGuardianWeapon::??));
}