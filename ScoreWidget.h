// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreWidget.generated.h"

/**
 * 
 */
UCLASS()
class PARAPONG_FINAL_API UScoreWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintImplementableEvent)
	void Player1ScoreChanged(int32 NewScore);

	UFUNCTION(BlueprintImplementableEvent)
	void Player2ScoreChanged(int32 NewScore);

	UFUNCTION(BlueprintImplementableEvent)
	void SetGameOverText(const FText& Text);

};
