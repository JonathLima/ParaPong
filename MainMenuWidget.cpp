// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(const UWorld* World = GetWorld())
	{
		if(APlayerController* PlayerController = World->GetFirstPlayerController())
		{
			PlayerController->bShowMouseCursor = true;

			const FInputModeUIOnly InputMode;
			PlayerController->SetInputMode(InputMode);
		}
	}
}