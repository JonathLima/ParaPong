// Fill out your copyright notice in the Description page of Project Settings.


#include "ParaPongPlayerController.h"
#include "ParaPong_Final.h"

void AParaPongPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis(TEXT("MoveRight"), this, &AParaPongPlayerController::MoveRight);
}


void AParaPongPlayerController::MoveRight(float Value)
{
	//UE_LOG(LogParaPong, Log, TEXT("Move Right: %f"), Value);
	
	
	if(APawn* ControlledPawn = GetPawn())
	{
		ControlledPawn->AddMovementInput(ControlledPawn->GetActorRightVector(), Value);
	}
}


