// Fill out your copyright notice in the Description page of Project Settings.

#include "Ball.h"
#include "ParaPong_Final.h"
#include <Kismet/KismetMathLibrary.h>

// Sets default values
ABall::ABall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallMesh"));
	SetRootComponent(BallMesh);

	//in event collision, Call the function OnBallHit.
	OnActorHit.AddDynamic(this, &ABall::OnBallHit);
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();

	Direction = GetRandomXYDirection();

	//Read a current position ball
	InitialLocation = GetActorLocation();

	// Enable "Simulation Generates Hit Events".
	BallMesh->SetNotifyRigidBodyCollision(true);
	// Move the Ball only in XY plane.
	BallMesh->SetConstraintMode(EDOFMode::XYPlane);
	// Enable Physics simulation Physics in Ball.
	StopMovement();
	// Set Mass 
	BallMesh->SetMassOverrideInKg(NAME_None, 1.0f, true);
	
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (BallMesh && BallMesh->IsSimulatingPhysics())
	{
		FVector const Force = Direction * 500.0f;
		BallMesh->AddForce(Force);
	}
}

void ABall::OnBallHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	Direction = UKismetMathLibrary::GetReflectionVector(Direction, Hit.Normal);
	UE_LOG(LogParaPong, Log, TEXT("Direction: %s"), *Direction.ToString());
	
}

void ABall::StartMovement()
{
	if(BallMesh)
	{
		Direction = GetRandomXYDirection();
		BallMesh->SetSimulatePhysics(true);
	}
}

void ABall::StopMovement()
{
	if(BallMesh)
	{
		BallMesh->SetSimulatePhysics(false);
	}
}

void ABall::ResetBall()
{
	SetActorLocation(InitialLocation);
}



FVector ABall::GetRandomXYDirection()
{
	FVector RandomDirection;
	do
	{
		RandomDirection = UKismetMathLibrary::RandomUnitVector();
		RandomDirection.Z = 0.0f;
	}
	while (!RandomDirection.Normalize());

	return RandomDirection;
}
