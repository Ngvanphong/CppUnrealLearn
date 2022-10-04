// Copyright Epic Games, Inc. All Rights Reserved.

#include "PhysicHandleCppGameMode.h"
#include "PhysicHandleCppCharacter.h"
#include "UObject/ConstructorHelpers.h"

APhysicHandleCppGameMode::APhysicHandleCppGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
