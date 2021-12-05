// Fill out your copyright notice in the Description page of Project Settings.


#include "ParaPongPlayerController.h"
#include "ParaPong_Final.h"
#include "ParaPongGameState.h"

void AParaPongPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis(TEXT("MoveRight"), this, &AParaPongPlayerController::MoveRight);
	InputComponent->BindAction(TEXT("Pause"), IE_Pressed, this, &AParaPongPlayerController::PauseGame);
}

void AParaPongPlayerController::PauseGame()
{
	UE_LOG(LogParaPong,Log, TEXT("Pause Game activate"))
	if(const UWorld* World = GetWorld())
	{
		if(AParaPongGameState* GameState = World->GetGameState<AParaPongGameState>())
		{
			GameState->PauseGame();
		}
	}
}

void AParaPongPlayerController::MoveRight(float Value)
{
	//UE_LOG(LogParaPong, Log, TEXT("Move Right: %f"), Value);
	
	
	if(APawn* ControlledPawn = GetPawn())
	{
		ControlledPawn->AddMovementInput(ControlledPawn->GetActorRightVector(), Value);
	}
}


