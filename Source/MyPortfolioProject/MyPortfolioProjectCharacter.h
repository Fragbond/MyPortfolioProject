// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "MyPortfolioProjectPickupActor.h"
#include "MyPortfolioProjectCharacter.generated.h"

class UInputComponent;
class UCameraComponent;

UCLASS(config=Game)
class MYPORTFOLIOPROJECT_API AMyPortfolioProjectCharacter : public ACharacter
{
	GENERATED_BODY()


		// Player camera
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* MyPortfolioProjectCameraComponent;

		// Adds pickup collision
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pickup, meta = (AllowPrivateAccess = "true"))
		class UCapsuleComponent* PickupCollision;

		// Input mapping context
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputMappingContext* DefaultMappingContext;

		// Jump input action
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* JumpAction;

		// Move input action
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* MoveAction;

		// Get vector input action
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* GetVectorAction;

		// Teleport to vector input action
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* TeleportToVectorAction;

		// Pickup input action
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* PickupAction;

		// Drop input action
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* DropAction;

		// Adds begin overlap to pickup collision
		UFUNCTION()
		void OnComponentBeginOverlap_Pickup(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,bool bFromSweep, const FHitResult& SweepResult);

		// Adds end overlap to pickup collision
		UFUNCTION()
		void OnComponentEndOverlap_Pickup(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
public:
	// Sets default values for this character's properties
	AMyPortfolioProjectCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaSeconds) override;

public:	

	// Look input action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	// Returns MyPortfolioProjectCameraComponent
	UCameraComponent* GetMyPortfolioProjectCameraComponent() const { return MyPortfolioProjectCameraComponent; }

protected:

	// Called for every movement input
	void Move(const FInputActionValue& Value);

	// Called for every look input
	void Look(const FInputActionValue& Value);

	// Called when pickup button is hit
	void Pickup(const FInputActionValue& Value);

	// Called when drop button is hit
	void Drop(const FInputActionValue& Value);

	// Called when player places teleporter down
	void GetVector(const FInputActionValue& Value);

	// Called when player teleport to location
	void TeleportToVector(const FInputActionValue& Value);

private:
	// The Character holding an item
	AMyPortfolioProjectCharacter* Character;

	// Sets pickup to NULL
	UPrimitiveComponent* GetPickupActor = NULL;

	// Gets players vector and rotator for the teleporter
	FVector DesiredTeleportPostion;
	FRotator DesiredTeleportRotation;
	FRotator DesiredTeleportCameraRotation;

	// Checks if player has use the teleporter
	bool HasPlacesDownTeleporter = false;
};
