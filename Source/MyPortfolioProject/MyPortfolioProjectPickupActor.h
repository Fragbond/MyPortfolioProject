// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "MyPortfolioProjectPickupActor.generated.h"

UCLASS()
class MYPORTFOLIOPROJECT_API AMyPortfolioProjectPickupActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyPortfolioProjectPickupActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MyMesh;

	UPROPERTY(EditAnywhere)
	USceneComponent* HoldingComp;

	// Rotates pick up actors
	UFUNCTION()
	void RotateActor();

	// Picks up actors
	UFUNCTION()
	void Pickup();

	// If player is holding an actor
	bool bHolding;
	// If actor should have gravity
	bool bGravity;

	FRotator ControlRotation;
	ACharacter* MyPortfolioProjectCharacter;
	UCameraComponent* PickupCamera;
	FVector ForwardVector;
};
