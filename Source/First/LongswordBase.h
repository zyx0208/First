// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "LongswordBase.generated.h"

/**
 * 
 */
UCLASS()
class FIRST_API ALongswordBase : public AWeaponBase
{
	GENERATED_BODY()

public:
	virtual void SetupSkills() override;

	virtual void Tick(float DeltaTime) override;

protected:
	ALongswordBase();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon") UStaticMeshComponent* WeaponMesh;
	
	//무기 애니메이션
	FTimeline SwingTimeline;
	UPROPERTY(EditAnywhere, Category = "Timeline") UCurveFloat* SwingCurve;
	UFUNCTION() void SwingTimelineUpdate(float value);
	UFUNCTION() void SwingTimelineFinished();
	
	//장검 공용 스킬 1 : 내려찍기
	void Smash();
};
