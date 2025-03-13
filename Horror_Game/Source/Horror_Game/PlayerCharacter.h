// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Components/SpotLightComponent.h>
#include <Camera/CameraComponent.h>
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputMappingContext.h"
#include "InputActionValue.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class HORROR_GAME_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

// Enhanced Input
protected:
	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	UInputMappingContext* InputMapping;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	UInputAction* FlashlightAction;

	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(EditAnywhere)
	USpotLightComponent* SpotLight;

	UPROPERTY(EditAnywhere)
	USpotLightComponent* InnerSpotLight;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Flashlight();
	void Interact();

};
