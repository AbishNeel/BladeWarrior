// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FIRSTPROJECT_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	/** Reference to the UMG asset in the editor */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets");
	TSubclassOf<class UUserWidget> HUDOverlayAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets");
	TSubclassOf<UUserWidget> WEnemyHealthBar;

	/** Variable to hold the widget after creating it */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets");
	UUserWidget* HUDOverlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets");
	UUserWidget* EnemyHealthBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets");
	TSubclassOf<UUserWidget> WPauseMenu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets");
	UUserWidget* PauseMenu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets");
	TSubclassOf<UUserWidget> WDeathScreen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets");
	UUserWidget* DeathScreen;

	FVector EnemyLocation;

	bool bEnemyHealthBarVisible;

	void DisplayEnemyHealthBar();

	void RemoveEnemyHealthBar();

	bool bPauseMenuVisible;

	bool bDeathScreenVisible;

	bool bHasGameEnded;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="HUD")
	void DisplayPauseMenu();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "HUD")
	void RemovePauseMenu();

	void TogglePauseMenu();

	void GameModeOnly();

	void DisplayDeathScreen();

	UFUNCTION(BlueprintCallable)
	void RestartGame();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
};
