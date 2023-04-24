// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPortfolioProjectPickupActor.h"
#include "MyPortfolioProjectCharacter.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyPortfolioProjectPickupActor::AMyPortfolioProjectPickupActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Creates pick up actor
	PickupActor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));
	PickupActor->SetSimulatePhysics(true);
}

// Called when the game starts or when spawned
void AMyPortfolioProjectPickupActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyPortfolioProjectPickupActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}