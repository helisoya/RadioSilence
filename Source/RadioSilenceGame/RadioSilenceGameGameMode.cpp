// Copyright Epic Games, Inc. All Rights Reserved.

#include "RadioSilenceGameGameMode.h"
#include "RadioSilenceGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

ARadioSilenceGameGameMode::ARadioSilenceGameGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
