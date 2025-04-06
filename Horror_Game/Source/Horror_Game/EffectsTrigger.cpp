// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectsTrigger.h"
#include "GameFramework/Character.h"
// Sets default values
AEffectsTrigger::AEffectsTrigger()
{
 //	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    RootComponent = TriggerBox;
    TriggerBox->SetBoxExtent(FVector(200.f, 200.f, 200.f)); // Adjust size

    TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    TriggerBox->SetCollisionResponseToAllChannels(ECR_Ignore);
    TriggerBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

    HorrorArtifact = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HorrorArtifact"));
    HorrorArtifact->SetupAttachment(RootComponent);
    HorrorArtifact->SetVisibility(false); // Hide at start

    AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
    AudioComponent->SetupAttachment(RootComponent);
    AudioComponent->bAutoActivate = false; // Don't play automatically

    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AEffectsTrigger::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AEffectsTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEffectsTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEffectsTrigger::CheckIfPlayerIsLooking(ACharacter* Player)
{
    FVector PlayerLocation = Player->GetActorLocation();
    FVector PlayerForward = Player->GetActorForwardVector();
    FVector ToArtifact = (HorrorArtifact->GetComponentLocation() - PlayerLocation).GetSafeNormal();

    float Dot = FVector::DotProduct(PlayerForward, ToArtifact);

    // 0.98 = ~11 degrees tolerance
    if (Dot > 0.98f)
    {
        HorrorArtifact->SetVisibility(false);
    }
}


void AEffectsTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor != this)
    {
        ACharacter* Player = Cast<ACharacter>(OtherActor);
        if (Player)
        {
            HorrorArtifact->SetVisibility(true);

            if (AudioComponent && !AudioComponent->IsPlaying())
            {
                AudioComponent->Play();
            }

            if (CameraShakeEffect)
            {
                GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(CameraShakeEffect);
            }

            FTimerHandle HideTimerHandle;
            GetWorldTimerManager().SetTimer(HideTimerHandle, [this]()
                {
                    HorrorArtifact->SetVisibility(false);
                }, 3.0f, false);

        }
    }
}