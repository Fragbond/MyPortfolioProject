// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPortfolioProjectCharacter.h"
#include "MyPortfolioProjectPickupActor.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
AMyPortfolioProjectCharacter::AMyPortfolioProjectCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create camera component
	MyPortfolioProjectCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	MyPortfolioProjectCameraComponent->SetupAttachment(GetCapsuleComponent());
	MyPortfolioProjectCameraComponent->bUsePawnControlRotation = true;

	HoldingComponent = CreateDefaultSubobject<USceneComponent>(TEXT("HoldingComponent"));
	HoldingComponent->SetRelativeLocation(FVector(0.000004, 53.999992, 10.000000));

	CurrentItem = NULL;
	bInspecting = false;

}

void AMyPortfolioProjectCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



	if (bInspecting)
	{
		if (bHoldingItem)
		{
			MyPortfolioProjectCameraComponent->SetFieldOfView(FMath::Lerp(MyPortfolioProjectCameraComponent->FieldOfView, 90.0f, 0.1f));
			HoldingComponent->SetRelativeLocation(FVector(50.0f, 0.0f, 0.0f));
			GetWorld()->GetFirstPlayerController()->PlayerCameraManager->ViewPitchMax = 179.90000002f;
			GetWorld()->GetFirstPlayerController()->PlayerCameraManager->ViewPitchMin = -179.90000002f;
			CurrentItem->RotateActor();
		}
		else
		{
			MyPortfolioProjectCameraComponent->SetFieldOfView(FMath::Lerp(MyPortfolioProjectCameraComponent->FieldOfView, 45.0f, 0.1f));
		}
	}
	else
	{
		MyPortfolioProjectCameraComponent->SetFieldOfView(FMath::Lerp(MyPortfolioProjectCameraComponent->FieldOfView, 90.0f, 0.1f));

		if (bHoldingItem)
		{
			HoldingComponent->SetRelativeLocation(FVector(50.0, 0.0f, 0.0f));
		}
	}
}

// Called when the game starts or when spawned
void AMyPortfolioProjectCharacter::BeginPlay()
{
	// Call the base class
	Super::BeginPlay();
	
	PitchMax = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->ViewPitchMax;
	PitchMin = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->ViewPitchMin;

	// Add input mapping context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

// Called to bind functionality to input
void AMyPortfolioProjectCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyPortfolioProjectCharacter::Move);
		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyPortfolioProjectCharacter::Look);
		// Pick up
		EnhancedInputComponent->BindAction(PickupAction, ETriggerEvent::Triggered, this, &AMyPortfolioProjectCharacter::Pickup);
		// Inspect
		EnhancedInputComponent->BindAction(InspectAction, ETriggerEvent::Triggered, this, &AMyPortfolioProjectCharacter::OnInspect);
		EnhancedInputComponent->BindAction(InspectAction, ETriggerEvent::Completed, this, &AMyPortfolioProjectCharacter::OnInspectReleased);
	}

}

void AMyPortfolioProjectCharacter::Move(const FInputActionValue& Value)
{
	// Input is a 2D Vector
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// Add movement
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AMyPortfolioProjectCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// Add yaw and pitch input
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AMyPortfolioProjectCharacter::Pickup()
{
	if (CurrentItem && !bInspecting)
	{
		ToggleItemPickup();
	}
}

void AMyPortfolioProjectCharacter::OnInspect()
{
	if (bHoldingItem)
	{
		LastRotation = GetControlRotation();
	}
	else
	{
		bInspecting = true;
	}
}

void AMyPortfolioProjectCharacter::OnInspectReleased()
{
	if (bInspecting && bHoldingItem)
	{
		GetController()->SetControlRotation(LastRotation);
		GetWorld()->GetFirstPlayerController()->PlayerCameraManager->ViewPitchMax = PitchMax;
		GetWorld()->GetFirstPlayerController()->PlayerCameraManager->ViewPitchMin = PitchMin;
	}
	else
	{
		bInspecting = false;
	}
}

void AMyPortfolioProjectCharacter::ToggleItemPickup()
{
	if (CurrentItem)
	{
		bHoldingItem = !bHoldingItem;
		CurrentItem->Pickup();

		if (!bHoldingItem)
		{
			CurrentItem = NULL;
		}
	}
}