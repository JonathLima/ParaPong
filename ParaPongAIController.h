// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ParaPongAIController.generated.h"

/**
 * 
 */
UCLASS()
class PARAPONG_FINAL_API AParaPongAIController : public AAIController
{
	GENERATED_BODY()
public:
	AParaPongAIController();

	void BeginPlay() override;

	void Tick(float DeltaTime) override;

	UPROPERTY()
	AActor* BallRef;
};
