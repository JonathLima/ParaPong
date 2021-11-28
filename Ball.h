// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"

UCLASS()
class PARAPONG_FINAL_API ABall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ball|Movement")
	FVector Direction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ball|Movement")
	FVector InitialLocation;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ball")
	class UStaticMeshComponent* BallMesh;

	UFUNCTION(Category = "Ball|Movement")
	void OnBallHit( AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit );
	
	UFUNCTION(BlueprintCallable, Category = "Ball|Movement")
	void StartMovement();
	
	UFUNCTION(BlueprintCallable, Category = "Ball|Movement")
	void StopMovement();
	
	UFUNCTION(BlueprintCallable, Category = "Ball|Movement")
	void ResetBall();

private:
	static FVector GetRandomXYDirection();
	
};
