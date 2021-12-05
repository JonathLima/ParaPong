// Fill out your copyright notice in the Description page of Project Settings.


// ReSharper disable All
#include "ParaPongGameState.h"
#include "ParaPongCharacter.h"
#include "Ball.h"
#include "ParaPong_Final.h"
#include "MainMenuWidget.h"
#include "ScoreWidget.h"
#include <Kismet/GameplayStatics.h>
#include <Camera/CameraActor.h>

AParaPongGameState::AParaPongGameState()
{
	Player1Score = 0;
	Player2Score = 0;
	ScoreToWin = 3;
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
	
	
}


void AParaPongGameState::IncrementScore(AParaPongCharacter* Player)
{
	if(Player == Player1Ref)
	{
		Player1Score++;
		CheckVictory(Player1Ref, Player1Score);
		if(ScoreWidget)
		{
			ScoreWidget->Player1ScoreChanged(Player1Score);

			if(bIsGameOver)
			{
				ScoreWidget->SetGameOverText(FText::FromName(TEXT("Player 1 Wins!")));
			}
		}
		
	}
	else if (Player == Player2Ref)
	{
		Player2Score++;
		CheckVictory(Player2Ref, Player2Score);

		if(ScoreWidget)
		{
			ScoreWidget->Player2ScoreChanged(Player2Score);

			if(bIsGameOver)
			{
				ScoreWidget->SetGameOverText(FText::FromName(TEXT("Player 2 Wins!")));
			}
		}
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
	else
	{
		BallRef->StopMovement();
		BallRef->ResetBall();

		// Wait 1 sec to start ball movement.
		const float TimerRate = 1.0f;
		const bool Bloop = false;
		GetWorldTimerManager().SetTimer(StartMovementTimer, BallRef, &ABall::StartMovement,TimerRate, Bloop);
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

void AParaPongGameState::SetupGame(AParaPongCharacter* Player1, AParaPongCharacter* Player2,
	ABall* Ball, ACameraActor* Camera, UMainMenuWidget* Menu, UScoreWidget* ScoreWdg, UUserWidget* PauseMenuWdg)
{
	Player1Ref = Player1;
	Player2Ref = Player2;
	BallRef = Ball;
	MainCamera = Camera;
	MainMenu = Menu;
	ScoreWidget = ScoreWdg;
	PauseMenuWidget = PauseMenuWdg;

	MainMenu->AddToViewport();
	MainMenu->OnBtnStartClicked.AddDynamic(this,&AParaPongGameState::OnPrepareToStarMatch);
	

}

void AParaPongGameState::OnPrepareToStarMatch()
{
	const float TimerRate = 1.0f; // frequency with which the timer will be called
	const bool BLoop = true; // if timer have applicant
	const float TimerDelay = 2.0f; // Delay to start timer
	
	// Start Game timer 
	GetWorldTimerManager().SetTimer(StartMatchTimer, this, &AParaPongGameState::OnStartMatchCountdown,
		TimerRate, BLoop, TimerDelay);

	if(MainMenu)
	{
		// Remove Game menu off screen
		MainMenu->RemoveFromParent();
		
		// Add Score after Game menu
		if(ScoreWidget)
		{
			// initialize score to zero!
			ScoreWidget->Player1ScoreChanged(0);
			ScoreWidget->Player2ScoreChanged(0);
			
			ScoreWidget->AddToViewport();
			UE_LOG(LogParaPong,Log, TEXT("ScoreWidget Adicionado na Tela"));
		}
		
		
		
		if(UWorld* World = GetWorld())
		{	
			if(APlayerController* PlayerController = World->GetFirstPlayerController())
			{
				PlayerController->bShowMouseCursor = false;
				FInputModeGameOnly InputMode;
				PlayerController->SetInputMode(InputMode);
			}
		}
	}
	
}

void AParaPongGameState::PauseGame()
{
	if(PauseMenuWidget)
	{
		if(UWorld* World = GetWorld())
		{
			if(APlayerController* PlayerController = World->GetFirstPlayerController())
			{
				PlayerController->bShowMouseCursor = true;
				FInputModeUIOnly InputMode;
				PlayerController->SetInputMode(InputMode);
				PlayerController->Pause();
			}
		}
		PauseMenuWidget->AddToViewport();
	}
}