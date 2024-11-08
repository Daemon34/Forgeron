// Copyright Epic Games, Inc. All Rights Reserved.

#include "ForgeronGameMode.h"
#include "ForgeronCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "FE_PlayerController.h"

AForgeronGameMode::AForgeronGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	PlayerControllerClass = AFE_PlayerController::StaticClass();
}
