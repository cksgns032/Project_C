// Copyright Epic Games, Inc. All Rights Reserved.

#include "CharacterMoveGameMode.h"
#include "CharacterMoveCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACharacterMoveGameMode::ACharacterMoveGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
