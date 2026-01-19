// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponAttack.h"
#include "DrawDebugHelpers.h"

// Sets default values
AWeaponAttack::AWeaponAttack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    AttackCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
    AttackCollision->OnComponentBeginOverlap.AddDynamic(this, &AWeaponAttack::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AWeaponAttack::BeginPlay()
{
	Super::BeginPlay();
    AttackCollision->SetSphereRadius(Radius);
    SetLifeSpan(LifeTime);
}

// Called every frame
void AWeaponAttack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    // 공격 범위 시각화
    if (AttackCollision)
    {
        FVector Center = AttackCollision->GetComponentLocation();
        float SphereRadius = AttackCollision->GetScaledSphereRadius(); // 콜리전 Sphere 크기

        DrawDebugSphere(GetWorld(), Center, SphereRadius, 16, FColor::Red,false, -1.f, 0, 2.f);
    }
}

void AWeaponAttack::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && !AlreadyHit.Contains(OtherActor))
    {
        UE_LOG(LogTemp, Log, TEXT("Attack!"));
        //UGameplayStatics::ApplyDamage(OtherActor, AttackDamage, nullptr, InstigatorRef, nullptr);
        AlreadyHit.Add(OtherActor);
    }
}

