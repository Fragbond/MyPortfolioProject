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

		// Input mapping context
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputMappingContext* DefaultMappingContext;

		// Jump input action
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* JumpAction;

		// Move input action
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* MoveAction;

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* PickupAction;

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		class UInputAction* InspectAction;

		// Holding component
		UPROPERTY(EditAnywhere)
		class USceneComponent* HoldingComponent;

		// Current item player is holding
		UPROPERTY(EditAnywhere)
		class AMyPortfolioProjectPickupActor* CurrentItem;

		// If holding item and is inspecting item
		bool bHoldingItem;
		bool bInspecting;

		// Item rotation camera
		float PitchMax;
		float PitchMin;

		// Item rotation vectors
		FVector HoldingComp;
		FRotator LastRotation;
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

	void Pickup();

	// Call on inspect button
	void OnInspect();

	// Releases inspected item on call
	void OnInspectReleased();

	void ToggleItemPickup();
};
