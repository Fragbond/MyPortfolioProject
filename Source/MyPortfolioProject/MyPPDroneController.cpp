// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPPDroneController.h"
#include "MyPPDroneCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

AMyPPDroneController::AMyPPDroneController()
{
	// Sets Behavior tree
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComp"));
	check(BehaviorTreeComponent);
	// Sets blackboard
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
	check(BlackboardComponent);
}

void AMyPPDroneController::OnPossess(APawn* InPawn)
{
	// Run Behavior tree
	Super::OnPossess(InPawn);
	if (InPawn == nullptr)
	{
		return;
	}
	AMyPPDroneCharacter* Drone = Cast<AMyPPDroneCharacter>(InPawn);
	if (Drone)
	{
		if (Drone->BehaviorTree)
		{
			BlackboardComponent->InitializeBlackboard(*(Drone->BehaviorTree->BlackboardAsset));
			BehaviorTreeComponent->StartTree(*(Drone->BehaviorTree));
		}
	}
}

UBlackboardComponent* AMyPPDroneController::GetBlackboard()
{
	return BlackboardComponent;
}