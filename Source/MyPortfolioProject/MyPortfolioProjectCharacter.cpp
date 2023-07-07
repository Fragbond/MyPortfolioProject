// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPortfolioProjectCharacter.h"
#include "MyPortfolioProjectPickupActor.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SocketSubsystem.h"
#include "Components/PrimitiveComponent.h"


// Sets default values
AMyPortfolioProjectCharacter::AMyPortfolioProjectCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create camera component
	MyPortfolioProjectCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	MyPortfolioProjectCameraComponent->SetupAttachment(GetCapsuleComponent());
	MyPortfolioProjectCameraComponent->bUsePawnControlRotation = true;

	// Creates pickup collision capsule
	PickupCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("PickupCollision"));
	PickupCollision->SetupAttachment(GetCapsuleComponent());
}

void AMyPortfolioProjectCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called when the game starts or when spawned
void AMyPortfolioProjectCharacter::BeginPlay()
{
	// Call the base class
	Super::BeginPlay();

	// Add input mapping context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	// Creates begin overlap for pickup collision
	PickupCollision->OnComponentBeginOverlap.AddDynamic(this, &AMyPortfolioProjectCharacter::OnComponentBeginOverlap_Pickup);
	PickupCollision->OnComponentEndOverlap.AddDynamic(this, &AMyPortfolioProjectCharacter::OnComponentEndOverlap_Pickup);
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
		// Pickup
		EnhancedInputComponent->BindAction(PickupAction, ETriggerEvent::Triggered, this, &AMyPortfolioProjectCharacter::Pickup);
		// Drop
		EnhancedInputComponent->BindAction(DropAction, ETriggerEvent::Triggered, this, &AMyPortfolioProjectCharacter::Drop);
		// Get Vector
		EnhancedInputComponent->BindAction(GetVectorAction, ETriggerEvent::Triggered, this, &AMyPortfolioProjectCharacter::GetVector);
		// Teleport to vector
		EnhancedInputComponent->BindAction(TeleportToVectorAction, ETriggerEvent::Triggered, this, &AMyPortfolioProjectCharacter::TeleportToVector);
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

void AMyPortfolioProjectCharacter::Drop(const FInputActionValue& Value)
{
	if (Controller != nullptr)
	{
		if (GetPickupActor == NULL)
		{
			// Tells player to pick up something to use drop
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("You need to pick up an object to use drop."));
		}
		else
		{
			// Turns on gravity for actor
			GetPickupActor->SetSimulatePhysics(true);
			// Detach pickup item from pickup socket
			GetPickupActor->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		}
	}
}

void AMyPortfolioProjectCharacter::Pickup(const FInputActionValue& Value)
{
	if (Controller != nullptr)
	{
		if (GetPickupActor == NULL)
		{
			// Tells player to get closer
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("You need to get closer to use pickup."));
		}
		else
		{
			// Turns off gravity for actor
			GetPickupActor->SetSimulatePhysics(false);
			// Attach pickup item to pickup socket
			FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
			GetPickupActor->AttachToComponent(FindComponentByClass<USkeletalMeshComponent>(), AttachmentRules, TEXT("Pickup Socket"));
		}
	}
}

void AMyPortfolioProjectCharacter::GetVector(const FInputActionValue& Value)
{
	if (Controller != nullptr)
	{
		DesiredTeleportPostion = GetActorLocation();
		DesiredTeleportRotation = GetActorRotation();
		DesiredTeleportCameraRotation = GetControlRotation();
		HasPlacesDownTeleporter = true;
	}
}

void AMyPortfolioProjectCharacter::TeleportToVector(const FInputActionValue& Value)
{
	if (Controller != nullptr)
	{
		if (HasPlacesDownTeleporter == true)
		{
			TeleportTo(DesiredTeleportPostion, DesiredTeleportRotation);
			GetController()->SetControlRotation(DesiredTeleportCameraRotation);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("You need to place drop the teleporter in order to use it."));
		}
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

void AMyPortfolioProjectCharacter::OnComponentBeginOverlap_Pickup(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,bool bFromSweep, const FHitResult& SweepResult)
{
	AMyPortfolioProjectPickupActor* PickupActor = Cast<AMyPortfolioProjectPickupActor>(OtherActor);
	if (PickupActor)
	{
		// Gets the pick up actor
		GetPickupActor = OtherComp;
	}
}

void AMyPortfolioProjectCharacter::OnComponentEndOverlap_Pickup(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AMyPortfolioProjectPickupActor* PickupActor = Cast<AMyPortfolioProjectPickupActor>(OtherActor);
	if (PickupActor)
	{
		// Sets actor to NULL
		GetPickupActor = NULL;
	}
}