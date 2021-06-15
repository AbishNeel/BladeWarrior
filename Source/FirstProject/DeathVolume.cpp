// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathVolume.h"
#include"Components/BoxComponent.h"
#include "Components/BillboardComponent.h"
#include "Main.h"

// Sets default values
ADeathVolume::ADeathVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetupAttachment(GetRootComponent());

	Billboard= CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	Billboard->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ADeathVolume::BeginPlay()
{
	Super::BeginPlay();
	
	Box->OnComponentBeginOverlap.AddDynamic(this, &ADeathVolume::OnOverlapBegin);
}

// Called every frame
void ADeathVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADeathVolume::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		AMain* Main = Cast<AMain>(OtherActor);
		if (Main)
		{
			Main->Die();
		}
	}
}