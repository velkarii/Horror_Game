// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/AudioComponent.h"
#include "Camera/CameraShakeBase.h"
#include "Kismet/GameplayStatics.h"
#include "EffectsTrigger.generated.h"

UCLASS()
class HORROR_GAME_API AEffectsTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEffectsTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
    UPROPERTY(VisibleAnywhere, Category = "Trigger")
    UBoxComponent* TriggerBox;

    UPROPERTY(VisibleAnywhere, Category = "Horror Effect")
    UStaticMeshComponent* HorrorArtifact;

    UPROPERTY(VisibleAnywhere, Category = "Audio")
    UAudioComponent* AudioComponent;

    UPROPERTY(EditAnywhere, Category = "Effects")
    TSubclassOf<UCameraShakeBase> CameraShakeEffect;

    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
        bool bFromSweep, const FHitResult& SweepResult);
};
