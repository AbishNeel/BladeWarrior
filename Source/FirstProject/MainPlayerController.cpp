// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (HUDOverlayAsset)
	{
		HUDOverlay = CreateWidget<UUserWidget>(this, HUDOverlayAsset);
	}
	HUDOverlay->AddToViewport();
	HUDOverlay->SetVisibility(ESlateVisibility::Visible);

	if (WEnemyHealthBar)
	{
		EnemyHealthBar = CreateWidget<UUserWidget>(this, WEnemyHealthBar);
		if (EnemyHealthBar)
		{
			EnemyHealthBar->AddToViewport();
			EnemyHealthBar->SetVisibility(ESlateVisibility::Hidden);
		}
		FVector2D Alignment(0.f, 0.f);
		EnemyHealthBar->SetAlignmentInViewport(Alignment);
	}

	if (WPauseMenu)
	{
		PauseMenu = CreateWidget<UUserWidget>(this, WPauseMenu);
		if (PauseMenu)
		{
			PauseMenu->AddToViewport();
			PauseMenu->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	if (WDeathScreen)
	{
		DeathScreen = CreateWidget<UUserWidget>(this, WDeathScreen);
		if (DeathScreen)
		{
			DeathScreen->AddToViewport();
			DeathScreen->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	bDeathScreenVisible = false;
	bHasGameEnded = false;
}

void AMainPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (EnemyHealthBar)
	{
		FVector2D PositionInViewport;
		ProjectWorldLocationToScreen(EnemyLocation, PositionInViewport);
		PositionInViewport.Y -= 100.f;

		FVector2D SizeInViewport(200.f, 25.f);

		EnemyHealthBar->SetPositionInViewport(PositionInViewport);
		EnemyHealthBar->SetDesiredSizeInViewport(SizeInViewport);
	}
}

void AMainPlayerController::DisplayEnemyHealthBar()
{
	bEnemyHealthBarVisible = true;
	EnemyHealthBar->SetVisibility(ESlateVisibility::Visible);
}

void AMainPlayerController::RemoveEnemyHealthBar()
{
	bEnemyHealthBarVisible = false;
	EnemyHealthBar->SetVisibility(ESlateVisibility::Hidden);
}

void AMainPlayerController::DisplayPauseMenu_Implementation()
{
	if (PauseMenu && !bHasGameEnded)
	{
		bPauseMenuVisible = true;
		PauseMenu->SetVisibility(ESlateVisibility::Visible);
		UGameplayStatics::SetGamePaused(GetWorld(), true);

		FInputModeGameAndUI InputMode;

		SetInputMode(InputMode);
		bShowMouseCursor = true;
	}
}

void AMainPlayerController::RemovePauseMenu_Implementation()
{
	UGameplayStatics::SetGamePaused(GetWorld(), false);

	bPauseMenuVisible = false;
	bShowMouseCursor = false;
	GameModeOnly();
}

void AMainPlayerController::TogglePauseMenu()
{
	if (bPauseMenuVisible)
	{
		RemovePauseMenu();
	}
	else
	{
		DisplayPauseMenu();
	}
}

void AMainPlayerController::GameModeOnly()
{
	FInputModeGameOnly InputMode;

	SetInputMode(InputMode);
}

void AMainPlayerController::DisplayDeathScreen()
{
	bDeathScreenVisible = true;
	bHasGameEnded = true;
    
	if (DeathScreen)
	{
		DeathScreen->SetVisibility(ESlateVisibility::Visible);
	}
	HUDOverlay->SetVisibility(ESlateVisibility::Hidden);
	EnemyHealthBar->SetVisibility(ESlateVisibility::Hidden);

	FInputModeGameAndUI InputMode;

	SetInputMode(InputMode);
	bShowMouseCursor = true;
}

void AMainPlayerController::RestartGame()
{
	bDeathScreenVisible = false;
	bHasGameEnded = false;

	if (DeathScreen)
	{
		DeathScreen->SetVisibility(ESlateVisibility::Hidden);
	}
	HUDOverlay->SetVisibility(ESlateVisibility::Visible);

	bShowMouseCursor = false;
	GameModeOnly();

	UGameplayStatics::OpenLevel(this, "SunTemple", false);
}