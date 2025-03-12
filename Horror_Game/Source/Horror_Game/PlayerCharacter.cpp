// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

bool flashlightMode = false;

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set Max Walk Speed
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	
	// Set Up SpringArmComponent For Flashlight
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 20.0f;
	SpringArmComp->bEnableCameraLag = true;
	SpringArmComp->bEnableCameraRotationLag = true;

	// Setp Up Flashlight's Light And Attach it To SpringArmComp
	SpotLight = CreateDefaultSubobject<USpotLightComponent>("SpotLight");
	SpotLight->SetupAttachment(SpringArmComp);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// Flashlight
	if (flashlightMode)
	{
		APlayerCharacter::SpotLight->SetVisibility(1);
	}
	else {
		APlayerCharacter::SpotLight->SetVisibility(0);
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMapping, 0);
		}
	}

	if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		Input->BindAction(InteractAction, ETriggerEvent::Started, this, &APlayerCharacter::Interact);
		Input->BindAction(FlashlightAction, ETriggerEvent::Started, this, &APlayerCharacter::Flashlight);
	}
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardDirection, MovementVector.Y);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(RightDirection, MovementVector.X);
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();
	AddControllerPitchInput(LookAxisVector.Y);
	AddControllerYawInput(LookAxisVector.X);
}

void APlayerCharacter::Flashlight()
{
	if (flashlightMode)
	{
		flashlightMode = false;
	}
	else {
		flashlightMode = true;
	}
}

void APlayerCharacter::Interact()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("Pressed"));
}
