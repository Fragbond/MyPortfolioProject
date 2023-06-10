// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPPDroneCharacter.h"
#include "MyPPDroneController.h"
#include "BehaviorTree/BlackboardComponent.h"

// Sets default values
AMyPPDroneCharacter::AMyPPDroneCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyPPDroneCharacter::BeginPlay()
{
	Super::BeginPlay();

	for (auto PatrolPoint : PatrolPoints)
	{
		WorldPatrolPoints.Add(PatrolPoint + GetActorLocation());
	}
}

const FVector& AMyPPDroneCharacter::GetNextPatrolLocation()
{
	if (WorldPatrolPoints.Num() > 0)
	{
		if (CurrentPatrolIndex >= WorldPatrolPoints.Num())
		{
			CurrentPatrolIndex = 0;
		}
		return WorldPatrolPoints[CurrentPatrolIndex++];
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("No Patrol Locations set for Drone Actor"));
		return FVector::ZeroVector;
	}
}

// Called every frame
void AMyPPDroneCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


