// Fill out your copyright notice in the Description page of Project Settings.

#include "ScoreTrigger.h"
#include "ParaPong_Final.h"
#include "Ball.h"
#include "ParaPongCharacter.h"
#include "ParaPongGameState.h"
#include "Components/BoxComponent.h"

// Sets default values
AScoreTrigger::AScoreTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("ScoreTrigger"));

	BoxCollision->SetGenerateOverlapEvents(true);
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AScoreTrigger::OnTriggerBeginOverlap);

	SetRootComponent(BoxCollision);
}

void AScoreTrigger::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult & SweepResult)
{
	if(Player && Ball && (OtherActor == Ball))
	{
		UE_LOG(LogParaPong, Log, TEXT("Ball acertou o gatilho"));
		
		if(AParaPongGameState* GameState = GetWorld()->GetGameState<AParaPongGameState>())
		{
			GameState->IncrementScore(Player);
		}
		
	}
	
}