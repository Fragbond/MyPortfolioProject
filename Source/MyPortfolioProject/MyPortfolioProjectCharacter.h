// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "MyPortfolioProjectCharacter.generated.h"

class UInputComponent;
class UCameraComponent;

UCLASS(config=Game)
class MYPORTFOLIOPROJECT_API AMyPortfolioProjectCharacter : public ACharacter
{
	GENERATED_BODY()

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
public:
	// Sets default values for this character's properties
	AMyPortfolioProjectCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

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
};
