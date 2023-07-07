// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyPPDroneController.generated.h"

/**
 * 
 */
UCLASS()
class MYPORTFOLIOPROJECT_API AMyPPDroneController : public AAIController
{
	GENERATED_BODY()
	
public:
	AMyPPDroneController();

	// Creates get blackboard
	UBlackboardComponent* GetBlackboard();

	// Called when ai takes control of drone actor
	virtual void OnPossess(APawn* InPawn) override;

protected:
	// Creates behavior tree
	UPROPERTY(BlueprintReadWrite, Category = Behavior)
	class UBehaviorTreeComponent* BehaviorTreeComponent;

	// Creates blackboard
	UPROPERTY(BlueprintReadWrite, Category = Blackboard)
	class UBlackboardComponent* BlackboardComponent;
};
