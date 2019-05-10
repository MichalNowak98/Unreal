#include "Lamp.h"

ALamp::ALamp() : LightSource(CreateDefaultSubobject<UPointLightComponent>(TEXT("LightSource")))
{
	PrimaryActorTick.bCanEverTick = true;

	//if creating of UPointLightComponent was successful
	if (LightSource)
	{
		LightSource->SetIntensity(5000);
	}
}

void ALamp::BeginPlay()
{
	Super::BeginPlay();
	Player = GetWorld()->GetFirstPlayerController()->GetPawn();
	
}

void ALamp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (TriggerVolumeRed && TriggerVolumeGreen && TriggerVolumeBlue &&
		!TriggerVolumeRed->IsOverlappingActor(Player) && !TriggerVolumeGreen->IsOverlappingActor(Player) && !TriggerVolumeBlue->IsOverlappingActor(Player))
	{
		Color_on(White);
	}
	else
	{
		if (TriggerVolumeRed && TriggerVolumeRed->IsOverlappingActor(Player))
		{
			Color_on(Red);
		}
		else
		{
			Color_off(Red);
		}
		if (TriggerVolumeGreen && TriggerVolumeGreen->IsOverlappingActor(Player))
		{
			Color_on(Green);
		}
		else
		{
			Color_off(Green);
		}
		if (TriggerVolumeBlue && TriggerVolumeBlue->IsOverlappingActor(Player))
		{
			Color_on(Blue);
		}
		else
		{
			Color_off(Blue);
		}
	}
}

void ALamp::Toggle_Lamp()
{
	if(LightSource->Intensity == 0)
		LightSource->SetIntensity(5000);
	else
		LightSource->SetIntensity(0);
}
void ALamp::Color_on(EColor Color)
{
	FLinearColor color = LightSource->GetLightColor();
	if (Player)
	{
		switch (Color)
		{
		case White:
		{
			color.R = color.G = color.B = 1;
			break;
		}
		case Red:
		{
			color.R = 1;
			break;
		}
		case Green:
		{
			color.G = 1;
			break;
		}
		case Blue:
		{
			color.B = 1;
			break;
		}
		default: {}
		}
		LightSource->SetLightColor(color, true);
	}	
}

void ALamp::Color_off(EColor Color)
{
	FLinearColor color = LightSource->GetLightColor();
	if (Player)
	{
		switch (Color)
		{
		case Red:
		{
			color.R = 0;
			break;
		}
		case Green:
		{
			color.G = 0;
			break;
		}
		case Blue:
		{
			color.B = 0;
			break;
		}
		default: {}
		}
		LightSource->SetLightColor(color, true);
	}
}

