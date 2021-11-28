// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ParaPongPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PARAPONG_FINAL_API AParaPongPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void SetupInputComponent() override;

	void MoveRight(float Value);
};
