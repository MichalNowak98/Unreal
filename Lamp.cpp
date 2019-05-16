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
	TriggerVolumeRed = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Red"));
	TriggerVolumeGreen = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Green"));
	TriggerVolumeBlue =  CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Blue"));

	Color.R = Color.G = Color.B = 0;

	if (LightSource)
	{
		LightSource->SetIntensity(5000);
		LightSource->SetLightColor(FLinearColor(0, 0, 0, 1), true);
	}
}

void ALamp::TriggerRed(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor == Player)
	{
		Color_on(EColor::Red);
	}
	SetLightColor_Implementation(Color);

}

void ALamp::TriggerGreen(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor == Player)
	{
		Color_on(EColor::Green);
	}
	SetLightColor_Implementation(Color);
}

void ALamp::TriggerBlue(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor == Player)
	{
		Color_on(EColor::Blue);
	}
	SetLightColor_Implementation(Color);
}

void ALamp::TriggerRedEnd(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		Color_off(EColor::Red);
		SetLightColor_Implementation(Color);
	}
}

void ALamp::TriggerGreenEnd(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		Color_off(EColor::Green);
		SetLightColor_Implementation(Color);
	}
}

void ALamp::TriggerBlueEnd(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		Color_off(EColor::Blue);
		SetLightColor_Implementation(Color);
	}
}

// Called when the game starts or when spawned
void ALamp::BeginPlay()
{
	Super::BeginPlay();
	Player = GetWorld()->GetFirstPlayerController()->GetPawn();
	PlayerController = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());
	TriggerVolumeRed->OnComponentBeginOverlap.AddDynamic(this, &ALamp::TriggerRed);
	TriggerVolumeGreen->OnComponentBeginOverlap.AddDynamic(this, &ALamp::TriggerGreen);
	TriggerVolumeBlue->OnComponentBeginOverlap.AddDynamic(this, &ALamp::TriggerBlue);
	TriggerVolumeRed->OnComponentEndOverlap.AddDynamic(this, &ALamp::TriggerRedEnd);
	TriggerVolumeGreen->OnComponentEndOverlap.AddDynamic(this, &ALamp::TriggerGreenEnd);
	TriggerVolumeBlue->OnComponentEndOverlap.AddDynamic(this, &ALamp::TriggerBlueEnd);
}

// Called every frame
void ALamp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ALamp::Color_on(EColor Ecolor)
{
	if (Player)
	{
		switch (Ecolor)
		{
		case EColor::White:
		{
			Color.R = Color.G = Color.B = 1;
			break;
		}
		case EColor::Red:
		{
			Color.R = 1;
			break;
		}
		case EColor::Green:
		{
			Color.G = 1;
			break;
		}
		case EColor::Blue:
		{
			Color.B = 1;
			break;
		}
		default: {}
		}
	}
}

void ALamp::Color_off(EColor Ecolor)
{
	if (Player)
	{
		switch (Ecolor)
		{
		case EColor::Red:
		{
			Color.R = 0;
			break;
		}
		case EColor::Green:
		{
			Color.G = 0;
			break;
		}
		case EColor::Blue:
		{
			Color.B = 0;
			break;
		}
		default: {}
		}
	}

}

void ALamp::SetLightColor_Implementation(const FLinearColor & Color)
{
	LightSource->SetLightColor(Color);
}
