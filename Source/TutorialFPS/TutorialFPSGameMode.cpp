// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "TutorialFPSGameMode.h"
#include "TutorialFPSHUD.h"
#include "TutorialFPSCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATutorialFPSGameMode::ATutorialFPSGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ATutorialFPSHUD::StaticClass();
}
