// Fill out your copyright notice in the Description page of Project Settings.

#include "Lamp.h"

// Sets default values
ALamp::ALamp() : LightSource(CreateDefaultSubobject<UPointLightComponent>(TEXT("LightSource")))
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
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
}

// Called every frame
void ALamp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

