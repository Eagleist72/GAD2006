// Copyright Epic Games, Inc. All Rights Reserved.

#include "LabWork_1GameMode.h"
#include "LabWork_1Character.h"
#include "UObject/ConstructorHelpers.h"

ALabWork_1GameMode::ALabWork_1GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
