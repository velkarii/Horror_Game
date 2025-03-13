// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectsTrigger.h"

// Sets default values
AEffectsTrigger::AEffectsTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

