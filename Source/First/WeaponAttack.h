// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "WeaponAttack.generated.h"

UCLASS()
class FIRST_API AWeaponAttack : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeaponAttack();
	virtual void Tick(float DeltaTime) override;

	// 생성 시 주입될 값들
	int Damage;
	float Radius;
	float LifeTime;

protected:
	virtual void BeginPlay() override;

	//판정 구
	UPROPERTY(VisibleAnywhere) USphereComponent* AttackCollision;
	//오버렙 이벤트
	UFUNCTION() void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//이미 맞은 액터 관리
	UPROPERTY() TSet<AActor*> AlreadyHit;
};
