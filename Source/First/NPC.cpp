// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC.h"
#include "MyCharacter.h"
#include "SelectShop.h"

// Sets default values
ANPC::ANPC()
{
	PrimaryActorTick.bCanEverTick = true;

    InteractionRange = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionRange"));
    InteractionRange->InitSphereRadius(300.f);
    InteractionRange->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    InteractionRange->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    InteractionRange->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Overlap);

    RootComponent = InteractionRange;

    InteractionRange->OnComponentBeginOverlap.AddDynamic(this, &ANPC::OnSphereBeginOverlap);
    InteractionRange->OnComponentEndOverlap.AddDynamic(this, &ANPC::OnSphereEndOverlap);

    InteractUI = CreateDefaultSubobject<UBillboardComponent>(TEXT("InteractUI"));
    InteractUI->SetupAttachment(RootComponent);
    InteractUI->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
}

void ANPC::BeginPlay()
{
	Super::BeginPlay();
	
}

void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANPC::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (AMyCharacter* Player = Cast<AMyCharacter>(OtherActor))
    {
        if (InteractUI)
        {
            InteractUI->SetHiddenInGame(false);
            UE_LOG(LogTemp, Log, TEXT("Appear Interaction UI"));
        }
    }
}

void ANPC::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (AMyCharacter* Player = Cast<AMyCharacter>(OtherActor))
    {
        if (InteractUI)
        {
            InteractUI->SetHiddenInGame(true);
            UE_LOG(LogTemp, Log, TEXT("Disappear Interaction UI"));
        }
        if ((Player->ShopSelectUI) && (Player->ShopSelectUI->IsInViewport()))
        {
            Player->ShopSelectUI->RemoveFromParent();
            Player->PController->SetShowMouseCursor(false);
            Player->PController->SetInputMode(FInputModeGameOnly());
            Player->ShopSelectUI = nullptr;
        }
    }
}