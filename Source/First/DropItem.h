// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "ItemStructure.h"
#include "DropItem.generated.h"

UCLASS()
class FIRST_API ADropItem : public AActor
{
	GENERATED_BODY()
	
public:	
	ADropItem();
	ADropItem(int ItemIDValue, int CountValue);
	void SetingDropItem();
	virtual void Tick(float DeltaTime) override;

	//아이템 ID
	int ItemID;
	//아이템 수량
	int Count;

	UFUNCTION() void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	virtual void BeginPlay() override;

	//아이템 데이터 테이블
	UPROPERTY(EditAnywhere, BlueprintReadWrite) UDataTable* ItemDataTable;
	//아이템 벽
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) UStaticMeshComponent* ItemPlane;
	//아이템 머테리얼
	UPROPERTY(EditAnywhere, BlueprintReadWrite) UMaterialInterface* ItemMaterial;
	//아이템 머테리얼 인스턴스
	UPROPERTY(EditAnywhere, BlueprintReadOnly) UMaterialInstanceDynamic* ItemMaterialInstance;
	//콜리전
	UPROPERTY(EditAnywhere, BlueprintReadWrite) USphereComponent* Collision;
	
	//아이템 정보 찾기
	FItemStructure* SetingItemInfo(int ItemIDValue);
	
};
