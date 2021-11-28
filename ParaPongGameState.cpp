// Fill out your copyright notice in the Description page of Project Settings.


// ReSharper disable All
#include "ParaPongGameState.h"
#include "ParaPongCharacter.h"
#include "Ball.h"
#include "ParaPong_Final.h"
#include <Kismet/GameplayStatics.h>
#include <Camera/CameraActor.h>

AParaPongGameState::AParaPongGameState()
{
	Player1Score = 0;
	Player2Score = 0;
	ScoreToWin = 5;
	bIsGameOver = false;
	StartMatchCountdown = 1;
}

void AParaPongGameState::BeginPlay()
{
	Super::BeginPlay();

	// config GameCamera

	if(APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		PlayerController->SetViewTarget(MainCamera);
	}

	/*AActor* BallActor = UGameplayStatics::GetActorOfClass(GetWorld(), ABall::StaticClass());

	if(BallActor)
	{
		 Made cast AActor to ABall
		BallRef = Cast<ABall>(BallActor);
	}*/
	
	const float TimerRate = 1.0f; // frequency with which the timer will be called
	const bool BLoop = true; // if timer have applicant
	const float TimerDelay = 2.0f; // Delay to start timer
	
	// Start Game timer 
	GetWorldTimerManager().SetTimer(StartMatchTimer, this, &AParaPongGameState::OnStartMatchCountdown,
		TimerRate, BLoop, TimerDelay);
}


void AParaPongGameState::IncrementScore(AParaPongCharacter* Player)
{
	if(Player == Player1Ref)
	{
		Player1Score++;
		CheckVictory(Player1Ref, Player1Score);
	}
	else if (Player == Player2Ref)
	{
		Player2Score++;
		CheckVictory(Player2Ref, Player2Score);
	}
}

void AParaPongGameState::CheckVictory(AParaPongCharacter* Player, int32 Score)
{
	if (Score == ScoreToWin)
	{
		bIsGameOver = true;
		if(BallRef)
		{
			BallRef->StopMovement();
			BallRef->ResetBall();
		}
	}
}


void AParaPongGameState::OnStartMatchCountdown()
{
	UE_LOG(LogParaPong, Log, TEXT("Partida começa em %d s"), StartMatchCountdown);
	
	StartMatchCountdown--;

	if(StartMatchCountdown == 0)
	{
		UE_LOG(LogParaPong, Log, TEXT("Partida começou"));

		bIsGameOver = false;

		// End Game timer 
		GetWorldTimerManager().ClearTimer(StartMatchTimer);
		
		if(BallRef)
		{
			BallRef->StartMovement();
		}
		
	}
}

void AParaPongGameState::SetupGame(AParaPongCharacter* Player1, AParaPongCharacter* Player2, ABall* Ball, ACameraActor* Camera)
{
	Player1Ref = Player1;
	Player2Ref = Player2;
	BallRef = Ball;
	MainCamera = Camera;
}
