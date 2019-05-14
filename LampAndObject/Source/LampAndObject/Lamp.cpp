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
		LightSource->SetLightColor(FLinearColor(0,0,0,1), true);
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
	if (TriggerVolumeRed && TriggerVolumeRed->IsOverlappingActor(Player) && PlayerController)
	{
		PlayerController->Actualize_bRed(true);
	}
	else
	{
		if(PlayerController)
			PlayerController->Actualize_bRed(false);
	}
	if (TriggerVolumeGreen && TriggerVolumeGreen->IsOverlappingActor(Player) && PlayerController)
	{
		PlayerController->Actualize_bGreen(true);
	}
	else
	{
		if (PlayerController)
			PlayerController->Actualize_bGreen(false);
	}
	if (TriggerVolumeBlue && TriggerVolumeBlue->IsOverlappingActor(Player) && PlayerController)
	{
		PlayerController->Actualize_bBlue(true);
	}
	else
	{
		if (PlayerController)
			PlayerController->Actualize_bBlue(false);
	}
	if (HasAuthority())
	{
		int CountRed = 0;
		int CountGreen = 0;
		int CountBlue = 0;
		FLinearColor Color;
		for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
		{
			if (Iterator->IsValid())
			{
				AMyPlayerController *temp = Cast<AMyPlayerController>(Iterator->Get());
				CountRed += temp->Get_bRed();
				CountGreen += temp->Get_bGreen();
				CountBlue += temp->Get_bBlue();
			}
		}
		//if Count is bigger then zero, set 1 in according channel
		if (CountRed > 0)
			Color_on(EColor::Red, Color);
		else
			Color_off(EColor::Red, Color);
		if (CountGreen > 0)
			Color_on(EColor::Green, Color);
		else
			Color_off(EColor::Green, Color);
		if (CountBlue > 0)
			Color_on(EColor::Blue, Color);
		else
			Color_off(EColor::Blue, Color);
		SetLightColor(Color);
	}
}

void ALamp::Color_on(EColor Ecolor, FLinearColor& Color)
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

void ALamp::Color_off(EColor Ecolor, FLinearColor& Color)
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
