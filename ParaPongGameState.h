// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ParaPongCharacter.h"
#include "GameFramework/GameStateBase.h"
#include "ParaPongGameState.generated.h"

/**
 * 
 */
UCLASS()
class PARAPONG_FINAL_API AParaPongGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	AParaPongGameState();

	void BeginPlay() override;

	void IncrementScore(class AParaPongCharacter* Player);

	void CheckVictory(class AParaPongCharacter* Player, int32 Score);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 Player1Score;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 Player2Score;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 ScoreToWin;

	UPROPERTY(EditAnywhere)
	class ABall* BallRef;
	
	UPROPERTY(EditAnywhere)
	class AParaPongCharacter* Player1Ref;
	
	UPROPERTY(EditAnywhere)
	class AParaPongCharacter* Player2Ref;

	UPROPERTY(EditAnywhere)
	class ACameraActor* MainCamera;
	
	UFUNCTION(BlueprintCallable)
	void SetupGame(class AParaPongCharacter* Player1,class AParaPongCharacter* Player2 ,class ABall* Ball, class ACameraActor* Camera);
	
private:
	bool bIsGameOver;

	FTimerHandle StartMatchTimer;

	int32 StartMatchCountdown;

	UFUNCTION()
	void OnStartMatchCountdown();
};
