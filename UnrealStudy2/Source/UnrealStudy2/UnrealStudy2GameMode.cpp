// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealStudy2GameMode.h"
#include "UnrealStudy2HUD.h"
#include "UnrealStudy2Character.h"
#include "UObject/ConstructorHelpers.h"

AUnrealStudy2GameMode::AUnrealStudy2GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AUnrealStudy2HUD::StaticClass();
}
