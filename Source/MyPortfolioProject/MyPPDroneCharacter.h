// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyPPDroneCharacter.generated.h"

class UInputComponent;

UCLASS(config=Game)
class MYPORTFOLIOPROJECT_API AMyPPDroneCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyPPDroneCharacter();

	UPROPERTY(EditAnywhere, Category = "BehaviorTree")
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, Category = "Patrol", Meta = (MakeEditWidget))
	TArray<FVector> PatrolPoints;

	class AMyPPDroneController* MyPPDroneController;

	UFUNCTION(BlueprintCallable)
	const FVector& GetNextPatrolLocation();

private:
	TArray<FVector> WorldPatrolPoints;

	int CurrentPatrolIndex = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
