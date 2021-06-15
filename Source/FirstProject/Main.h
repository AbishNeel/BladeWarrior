// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Main.generated.h"

UENUM(BlueprintType)
enum class EMovementStatus : uint8
{
	EMS_Normal		UMETA(DisplayName="Normal"),
	EMS_Sprinting	UMETA(DisplayName="Sprinting"),
	EMS_Dead		UMETA(DisplayName = "Dead"),

	EMS_MAX			UMETA(DisplayName="DefaultMax")
};

UENUM(BlueprintType)
enum class EStaminaStatus : uint8
{
	ESS_Normal				UMETA(DisplayName = "Normal"),
    ESS_BelowMinimum		UMETA(DisplayName="BelowMinimum"),
	ESS_Exhausted			UMETA(DisplayName="Exhausted"),
	ESS_ExhaustedRecovering UMETA(DisplayName="ExhaustedRecovering"),

	ESS_MAX					UMETA(DisplayName="DefaultMax")
};

UCLASS()
class FIRSTPROJECT_API AMain : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMain();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controller")
	class AMainPlayerController* MainPlayerController;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category=Items)
	class AWeapon* WeaponEquipped;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Items)
	class AItem* OverlappedItem;

	TArray<FVector> PickupLocations;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Enums")
	EMovementStatus MovementStatus;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enums")
	EStaminaStatus StaminaStatus;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Running")
	float RunningSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Running")
	float SprintingSpeed;

	bool bShiftKeyDown;

	bool bLMBDown;

	bool bESCDown;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Combat")
	bool bHasCombatTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	FVector CombatTargetLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float StaminaDrainRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MinSprintStamina;

	/** Camera boom positioning the camera behind the player */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	class UParticleSystem* HitParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	class USoundCue* HitSound;

	/** Base turn rates to scale turning functions */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	float InterpSpeed;

	bool bInterpToEnemy;

	bool bMovingForward;

	bool bMovingRight;

	void SetInterpToEnemy(bool Interp);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat")
	class AEnemy* CombatTarget;

	FORCEINLINE void SetCombatTarget(AEnemy* Target) { CombatTarget = Target; }

	FRotator GetLookAtRotationYaw(FVector Target);

	/**
	/*
	/* Player stats
	/* 
	*/

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Stats")
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
	float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Stats")
	float MaxStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
	float Stamina;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Stats")
	int32 Coins;

	UPROPERTY(EditDefaultsOnly, Category="SaveData")
	TSubclassOf<class AItemStorage> WeaponStorage;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Called for fowards/backwards input */
	void MoveForward(float value);

	/**Called for sideways input */
	void MoveRight(float value);

	/** Called via input to turn at a given rate
	* @param Rate This is a normalized rate, i.e 1.0 means 100% of desired turn rate
	*/
	void TurnAtRate(float Rate);

	/** Called via input to turn at a given rate
	* @param Rate This is a normalized rate, i.e 1.0 means 100% of look up/down rate
	*/
	void LookUpAtRate(float Rate);

	void Turn(float Value);

	void LookUp(float Value);

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable)
	void IncrementCoins(int32 Amount);

	UFUNCTION(BlueprintCallable)
	void IncrementHealth(float Amount);

	void Die();

	UFUNCTION(BlueprintCallable)
	void DeathEnd();

	void SetMovementStatus(EMovementStatus Status);

	void ShiftKeyDown();

	void ShiftKeyUp();

	void LMBDown();

	void LMBUp();

	void ESCDown();

	void ESCUp();

	FORCEINLINE void SetStaminaStatus(EStaminaStatus Status) { StaminaStatus = Status; }

	UFUNCTION(BlueprintCallable)
	void ShowPickupLocations();

	void SetEquippedWeapon(AWeapon* Weapon);

	FORCEINLINE AWeapon* GetEquippedWeapon() { return WeaponEquipped; }
	
	FORCEINLINE void SetOverlappedItem(AItem* Item) { OverlappedItem = Item; }

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly , Category = "Anims")
	bool bAttacking;

	void Attack();

	virtual void Jump() override;

	UFUNCTION(BlueprintCallable)
	void AttackEnd();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Anims")
	class UAnimMontage* CombatMontage;

	UFUNCTION(BlueprintCallable)
	void PlaySound();

	FORCEINLINE void SetHasCombatTarget(bool HasTarget) { bHasCombatTarget = HasTarget; }

	void UpdateCombatTarget();

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Combat")
	TSubclassOf<AEnemy> EnemyFilter;

	void SwitchLevel(FName LevelName);

	UFUNCTION(BlueprintCallable)
	void SaveGame();
	
	UFUNCTION(BlueprintCallable)
	void LoadGame(bool SetPosition);

	void LoadGameNoSwitch();
};