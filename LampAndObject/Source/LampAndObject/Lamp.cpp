// Fill out your copyright notice in the Description page of Project Settings.

#include "Lamp.h"

ALamp::ALamp(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	//replication flags
	bReplicates = true;
	bNetLoadOnClient = true;
	bAlwaysRelevant = true;

	LightSource = CreateDefaultSubobject<UPointLightComponent>(TEXT("LightSource"));
	if (LightSource)
	{
		LightSource->SetIntensity(5000);
	}
}

// Called when the game starts or when spawned
void ALamp::BeginPlay()
{
	Super::BeginPlay();
	Player = GetWorld()->GetFirstPlayerController()->GetPawn();
	PlayerController = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());
}

// Called every frame
void ALamp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (TriggerVolumeRed && TriggerVolumeRed->IsOverlappingActor(Player))
	{

	}
	else
	{

	}
	if (TriggerVolumeGreen && TriggerVolumeGreen->IsOverlappingActor(Player))
	{

	}
	else
	{

	}
	if (TriggerVolumeBlue && TriggerVolumeBlue->IsOverlappingActor(Player))
	{

	}
	else
	{

	}
}


