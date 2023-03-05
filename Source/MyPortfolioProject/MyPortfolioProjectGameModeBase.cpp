// Copyright Epic Games, Inc. All Rights Reserved.


#include "MyPortfolioProjectGameModeBase.h"
#include "MyPortfolioProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMyPortfolioProjectGameModeBase::AMyPortfolioProjectGameModeBase()
	: Super()
{
	// Sets the default pawn class
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/PortfolioProject/Blueprints/BP_PortfolioProjectCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}