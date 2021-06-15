// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DeathVolume.generated.h"

UCLASS()
class FIRSTPROJECT_API ADeathVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADeathVolume();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Box")
	class UBoxComponent* Box;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Box")
	class UBillboardComponent* Billboard;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
