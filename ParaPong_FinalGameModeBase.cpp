// Copyright Epic Games, Inc. All Rights Reserved.


#include "ParaPong_FinalGameModeBase.h"
#include "ParaPongPlayerController.h"
#include "ParaPongCharacter.h"
#include "ParaPongGameState.h"


AParaPong_FinalGameModeBase::AParaPong_FinalGameModeBase()
{
	DefaultPawnClass = AParaPongCharacter::StaticClass();
	GameStateClass = AParaPongGameState::StaticClass();
	PlayerControllerClass = AParaPongPlayerController::StaticClass();
	
}