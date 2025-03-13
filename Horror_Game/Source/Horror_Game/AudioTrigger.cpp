// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioTrigger.h"
#include "Components/BoxComponent.h"
#include "Components/AudioComponent.h"
#include "GameFramework/Character.h"

// Sets default values
AAudioTrigger::AAudioTrigger()
{
    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    RootComponent = TriggerBox;
    TriggerBox->SetBoxExtent(FVector(200.f, 200.f, 200.f)); 

    TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    TriggerBox->SetCollisionResponseToAllChannels(ECR_Ignore);
    TriggerBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

    AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
    AudioComponent->SetupAttachment(RootComponent);
    AudioComponent->bAutoActivate = false; 

    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AAudioTrigger::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AAudioTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAudioTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAudioTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor != this)
    {
        if (AudioComponent && !AudioComponent->IsPlaying())
        {
            AudioComponent->Play();
        }
    }
}