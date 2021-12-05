// Fill out your copyright notice in the Description page of Project Settings.


#include "ParaPongCharacter.h"
#include <Components/CapsuleComponent.h>
#include <GameFramework/CharacterMovementComponent.h>

// Sets default values
AParaPongCharacter::AParaPongCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TempMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TempMesh"));
	TempMesh->SetupAttachment(GetCapsuleComponent());

	GetCharacterMovement()->MaxWalkSpeed = 1200.0f;
}

// Called when the game starts or when spawned
void AParaPongCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AParaPongCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AParaPongCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

