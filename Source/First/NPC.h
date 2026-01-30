// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/BillboardComponent.h"
#include "NPC.generated.h"

UCLASS()
class FIRST_API ANPC : public AActor
{
	GENERATED_BODY()
	
public:	
	ANPC();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	//상호작용 범위 구
	UPROPERTY(VisibleAnywhere) class USphereComponent* InteractionRange;
	//상호작용 안내 UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI") UBillboardComponent* InteractUI;

	UFUNCTION() void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION() void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
