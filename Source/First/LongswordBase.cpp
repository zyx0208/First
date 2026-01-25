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
    
    //애니메이션 관련 등록
    if (SwingCurve)
    {
        FOnTimelineFloat UpdateFunc;
        FOnTimelineEvent FinishedFunc;

        UpdateFunc.BindUFunction(this, FName("SwingTimelineUpdate"));
        FinishedFunc.BindUFunction(this, FName("SwingTimelineFinished"));

        SwingTimeline.AddInterpFloat(SwingCurve, UpdateFunc);
        SwingTimeline.SetTimelineFinishedFunc(FinishedFunc);
        SwingTimeline.SetLooping(false);
    }

    //공용 스킬 먼저 등록
    Super::SetupSkills();

    //장검 공용 스킬 등록
    AllSkills.Add(FSkillDelegate::CreateUObject(this, &ALongswordBase::Smash));
}

void ALongswordBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    //애니메이션 틱 등록
    SwingTimeline.TickTimeline(DeltaTime);
}

void ALongswordBase::SwingTimelineUpdate(float value)
{
    Root->SetRelativeLocation(FMath::Lerp(FVector(0.0f, -30.0f, 40.0f), FVector(30.0f, -30.0f, -35.0f), value));
    Root->SetRelativeRotation(FMath::Lerp(FRotator(0.0f, 0.0f, 0.0f), FRotator(-100.0f, 0.0f, 0.0f), value));
}

void ALongswordBase::SwingTimelineFinished()
{
    Root->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
    Root->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
    IsAttacking = false;
    UE_LOG(LogTemp, Log, TEXT("Timeline Finished"));
}

void ALongswordBase::Smash()
{
    //공격 시작
    IsAttacking = true;

    //지연 생성
    AWeaponAttack* Attack = GetWorld()->SpawnActorDeferred<AWeaponAttack>(AWeaponAttack::StaticClass(), FTransform::Identity);
    if (!Attack) return;
    //공격 범위 붙이기
    Attack->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
    //공격 위치 설정
    Attack->SetActorRelativeLocation(FVector(0.0f, 0.0f, 50.0f));
    Attack->SetActorRelativeRotation(FRotator::ZeroRotator);
    //매개변수 주입
    Attack->Damage = 30.f;
    Attack->Radius = 20.f;
    Attack->LifeTime = 0.5f;
    //생성 완료
    Attack->FinishSpawning(FTransform::Identity);

    //검 움직임
    SwingTimeline.PlayFromStart();

    UE_LOG(LogTemp, Log, TEXT("LongSword HorizontalSlash executed!"));
}