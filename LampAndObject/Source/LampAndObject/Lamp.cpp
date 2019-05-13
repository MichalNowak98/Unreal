// Fill out your copyright notice in the Description page of Project Settings.


#include "Lamp.h"


ALamp::ALamp(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	CountRed = 0;
	CountGreen = 0;
	CountBlue = 0;
	TriggerVolumeRedPushed = false;
	TriggerVolumeGreenPushed = false;
	TriggerVolumeBluePushed = false;

	LightSource = CreateDefaultSubobject<UPointLightComponent>(TEXT("LightSource"));
	SetReplicates(true);
	bReplicates = true;
	bNetLoadOnClient = true;
	bAlwaysRelevant = true;

	if (GetWorld())
		PlayerController = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());

	//if creating of UPointLightComponent was successful
	if (LightSource)
	{
		LightSource->SetIntensity(5000);
		color = LightSource->GetLightColor();
	}
}

void ALamp::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ALamp, color);
	DOREPLIFETIME(ALamp, CountRed);
	DOREPLIFETIME(ALamp, CountGreen);
	DOREPLIFETIME(ALamp, CountBlue);
}

void ALamp::SetLightColor_Implementation(const FLinearColor Color)
{
	//color = Color;
	if (HasAuthority())
	{
		if (color.R == 1)
		{
			UE_LOG(LogTemp, Warning, TEXT("ServerRED"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("ServerNoRED"));
		}
		if (color.B == 1)
		{
			UE_LOG(LogTemp, Warning, TEXT("ServerBlue"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("ServerNoBlue"));
		}
		if (color.G == 1)
		{
			UE_LOG(LogTemp, Warning, TEXT("ServerGREEN"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("ServerNoGREEN"));
		}
	}
	else
	{
		if (color.R == 1)
		{
			UE_LOG(LogTemp, Warning, TEXT("ClientRED"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("ClientNoRED"));
		}
		if (color.B == 1)
		{
			UE_LOG(LogTemp, Warning, TEXT("ClientBlue"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("ClientNoBlue"));
		}
		if (color.G == 1)
		{
			UE_LOG(LogTemp, Warning, TEXT("ClientGREEN"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("ClientNoGREEN"));
		}
	}
	LightSource->SetLightColor(color, true);
}

void ALamp::increment_CountRed_Implementation()
{
	CountRed++;
	UE_LOG(LogTemp, Warning, TEXT("Client cos robi!"));
}

bool ALamp::increment_CountRed_Validate()
{
	return true;
}

void ALamp::increment_CountGreen_Implementation()
{
	CountGreen++;
}

bool ALamp::increment_CountGreen_Validate()
{
	return true;
}

void ALamp::increment_CountBlue_Implementation()
{
	CountBlue++;
}

bool ALamp::increment_CountBlue_Validate()
{
	return true;
}

void ALamp::decrement_CountRed_Implementation()
{
	CountRed--;
}

bool ALamp::decrement_CountRed_Validate()
{
	return true;
}

void ALamp::decrement_CountGreen_Implementation()
{
	CountGreen--;
}

bool ALamp::decrement_CountGreen_Validate()
{
	return true;
}

void ALamp::decrement_CountBlue_Implementation()
{
	CountBlue--;
}

bool ALamp::decrement_CountBlue_Validate()
{
	return true;
}

void ALamp::BeginPlay()
{
	Super::BeginPlay();
	Player = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void ALamp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TriggerVolumeRed && TriggerVolumeRed->IsOverlappingActor(Player))
	{
		if (!TriggerVolumeRedPushed)
		{
			increment_CountRed();
			if (!HasAuthority())
			{
				PlayerController->Server_Set_CountRed(CountRed);
			}
		}
		TriggerVolumeRedPushed = true;
	}
	else
	{
		if (TriggerVolumeRedPushed)
		{
			decrement_CountRed();
			if (!HasAuthority())
			{
				PlayerController->Server_Set_CountRed(CountRed);
			}
		}
		TriggerVolumeRedPushed = false;
	}
	if (TriggerVolumeGreen && TriggerVolumeGreen->IsOverlappingActor(Player))
	{
		if (!TriggerVolumeGreenPushed)
		{
			increment_CountGreen();
			if (!HasAuthority())
			{
				PlayerController->Server_Set_CountGreen(CountGreen);
			}
		}
			
		TriggerVolumeGreenPushed = true;
	}
	else
	{
		if (TriggerVolumeGreenPushed)
		{
			decrement_CountGreen();
			if (!HasAuthority())
			{
				PlayerController->Server_Set_CountGreen(CountGreen);
			}
		}
			
		TriggerVolumeGreenPushed = false;
	}
	if (TriggerVolumeBlue && TriggerVolumeBlue->IsOverlappingActor(Player))
	{
		if (!TriggerVolumeBluePushed)
		{
			increment_CountBlue();
			if (!HasAuthority())
			{
				PlayerController->Server_Set_CountBlue(CountBlue);
			}
		}
			
		TriggerVolumeBluePushed = true;
	}
	else
	{
		if (TriggerVolumeBluePushed)
		{
			decrement_CountBlue();
			if (!HasAuthority())
			{
				PlayerController->Server_Set_CountBlue(CountBlue);
			}
		}
			
		TriggerVolumeBluePushed = false;
	}
	if (HasAuthority())
	{
		UE_LOG(LogTemp, Warning, TEXT("CountRed: %d"), CountRed);
		UE_LOG(LogTemp, Warning, TEXT("CountGreen: %d"), CountGreen);
		UE_LOG(LogTemp, Warning, TEXT("CountBlue: %d"), CountBlue);
	}

	if (HasAuthority())
	{
		CountRed = AMyPlayerController::Server_Get_CountRed();
		CountGreen = AMyPlayerController::Server_Get_CountGreen();
		CountBlue = AMyPlayerController::Server_Get_CountBlue();
	}
	if (CountRed > 0)
	{
		Color_on(EColor::Red);
		//UE_LOG(LogTemp, Warning, TEXT("RED"));
	}
	else
	{
		Color_off(EColor::Red);
		//UE_LOG(LogTemp, Warning, TEXT("NORED"));
	}
	if (CountGreen > 0)
	{
		Color_on(EColor::Green);
		//UE_LOG(LogTemp, Warning, TEXT("GREEN"));
	}
	else
	{
		Color_off(EColor::Green);
		//UE_LOG(LogTemp, Warning, TEXT("NOGREEN"));
	}
	if (CountBlue > 0)
	{
		Color_on(EColor::Blue);
		//UE_LOG(LogTemp, Warning, TEXT("BLUE"));
	}
	else
	{
		Color_off(EColor::Blue);
		//UE_LOG(LogTemp, Warning, TEXT("NOBLUE"));
	}
	SetLightColor(color);
}

void ALamp::Toggle_Lamp()
{
	if (LightSource->Intensity == 0)
		LightSource->SetIntensity(5000);
	else
		LightSource->SetIntensity(0);
}
void ALamp::Color_on(EColor Color)
{
	if (Player)
	{
		switch (Color)
		{
		case EColor::White:
		{
			color.R = color.G = color.B = 1;
			break;
		}
		case EColor::Red:
		{
			color.R = 1;
			break;
		}
		case EColor::Green:
		{
			color.G = 1;
			break;
		}
		case EColor::Blue:
		{
			color.B = 1;
			break;
		}
		default: {}
		}
	}
}
void ALamp::Color_off(EColor Color)
{
	if (Player)
	{
		switch (Color)
		{
		case EColor::Red:
		{
			color.R = 0;
			break;
		}
		case EColor::Green:
		{
			color.G = 0;
			break;
		}
		case EColor::Blue:
		{
			color.B = 0;
			break;
		}
		default: {}
		}
	}

}

