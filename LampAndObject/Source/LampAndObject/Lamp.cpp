// Fill out your copyright notice in the Description page of Project Settings.

#include "Lamp.h"

ALamp::ALamp(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	//replication flags
	bReplicates = true;
	bNetLoadOnClient = true;
	bAlwaysRelevant = true;

	ALamp::NextID = 1;
	LightSource = CreateDefaultSubobject<UPointLightComponent>(TEXT("LightSource"));

	TriggerVolumeRed = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Component Red"));
	TriggerVolumeGreen = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Component Green"));
	TriggerVolumeBlue = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Component Blue"));
	ToggleSwitch = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Component ToggleSwitch"));
	TriggerVolumeRed->SetupAttachment(LightSource);
	TriggerVolumeGreen->SetupAttachment(LightSource);
	TriggerVolumeBlue->SetupAttachment(LightSource);
	ToggleSwitch->SetupAttachment(LightSource);

	bTurnedOn = true;

	if (LightSource)
	{
		LightSource->SetIntensity(5000);
		LightSource->SetLightColor(FLinearColor(0, 0, 0, 1), true);
	}
}

void ALamp::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ALamp, ID);
	DOREPLIFETIME(ALamp, bTurnedOn);
}

void ALamp::TriggerRedOn(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == Player && PlayerController)
	{
		PlayerController->Set_bColorRed(ID, true);
	}
}

void ALamp::TriggerGreenOn(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == Player && PlayerController)
	{
		PlayerController->Set_bColorGreen(ID, true);
	}
}

void ALamp::TriggerBlueOn(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == Player && PlayerController)
	{
		PlayerController->Set_bColorBlue(ID, true);
	}
}

void ALamp::TriggerRedOff(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == Player && PlayerController)
	{
		PlayerController->Set_bColorRed(ID, false);
	}
}

void ALamp::TriggerGreenOff(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == Player && PlayerController)
	{
		PlayerController->Set_bColorGreen(ID, false);
	}
}

void ALamp::TriggerBlueOff(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == Player && PlayerController)
	{
		PlayerController->Set_bColorBlue(ID, false);
	}
}

void ALamp::ToggleSwitchCallback(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == Player)
	{
		if (bTurnedOn)
		{
			bTurnedOn = false;
			if (PlayerController)
				PlayerController->Set_bToggleSwitch(ID, false);
			UE_LOG(LogTemp, Warning, TEXT("server turns off"));
		}
		else
		{
			bTurnedOn = true;
			UE_LOG(LogTemp, Warning, TEXT("server turns on"));
			if (PlayerController)
				PlayerController->Set_bToggleSwitch(ID, true);
		}
	}
}

// Called when the game starts or when spawned
void ALamp::BeginPlay()
{
	Super::BeginPlay();
	Player = GetWorld()->GetFirstPlayerController()->GetPawn();
	PlayerController = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());
	if (HasAuthority())
	{
		ID = ALamp::NextID;
		ALamp::NextID++;
	}
	TriggerVolumeRed->OnComponentBeginOverlap.AddDynamic(this, &ALamp::TriggerRedOn);
	TriggerVolumeGreen->OnComponentBeginOverlap.AddDynamic(this, &ALamp::TriggerGreenOn);
	TriggerVolumeBlue->OnComponentBeginOverlap.AddDynamic(this, &ALamp::TriggerBlueOn);
	TriggerVolumeRed->OnComponentEndOverlap.AddDynamic(this, &ALamp::TriggerRedOff);
	TriggerVolumeGreen->OnComponentEndOverlap.AddDynamic(this, &ALamp::TriggerGreenOff);
	TriggerVolumeBlue->OnComponentEndOverlap.AddDynamic(this, &ALamp::TriggerBlueOff);
	ToggleSwitch->OnComponentBeginOverlap.AddDynamic(this, &ALamp::ALamp::ToggleSwitchCallback);
}

// Called every frame
void ALamp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (HasAuthority())
	{
		//only server need this variables
		//int CountRed = 0;
		//int CountGreen = 0;
		//int CountBlue = 0;
		//if lamp has been toggled in this iteration
		//bool bToggledLamp = false;
		FLinearColor Color;

		//for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
		//{
		//	AMyPlayerController* tempPlayerController = Cast<AMyPlayerController>(Iterator->Get());
		//	if (tempPlayerController)
		//	{
		//		//CountRed += tempPlayerController->Get_bRed(ID);
		//		//CountGreen += tempPlayerController->Get_bGreen(ID);
		//		//CountBlue += tempPlayerController->Get_bBlue(ID);
		//		if (!bToggledLamp && bTurnedOn && !tempPlayerController->Get_bToggleSwitch(ID))
		//		{
		//			bTurnedOn = false;
		//			bToggledLamp = true;
		//			UE_LOG(LogTemp, Warning, TEXT("turned off on server"));
		//		}
		//		else if (!bToggledLamp && !bTurnedOn && tempPlayerController->Get_bToggleSwitch(ID))
		//		{
		//			bTurnedOn = true;
		//			bToggledLamp = true;
		//			UE_LOG(LogTemp, Warning, TEXT("turned on on server"));
		//		}
		//	}
		//}
		//if Count is bigger then zero, set 1 in according channel
		/*if (CountRed > 0)
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
			Color_off(EColor::Blue, Color);*/
		if (PlayerController && PlayerController->Get_bRed(ID) > 0)
		{
			Color_on(EColor::Red, Color);
		}
		else
		{
			if (PlayerController)
				Color_off(EColor::Red, Color);
		}
		if (PlayerController && PlayerController->Get_bGreen(ID) > 0)
		{
			Color_on(EColor::Green, Color);
		}
		else
		{
			if (PlayerController)
				Color_off(EColor::Green, Color);
		}
		if (PlayerController && PlayerController->Get_bBlue(ID) > 0)
		{
			Color_on(EColor::Blue, Color);
		}
		else
		{
			if (PlayerController)
				Color_off(EColor::Blue, Color);
		}
		SetLightColor(Color);

		bTurnedOn = PlayerController->Get_bToggleSwitch(ID);
		ToggleLamp();
	}
}

void ALamp::Color_on(EColor Ecolor, FLinearColor& Color)
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

void ALamp::Color_off(EColor Ecolor, FLinearColor& Color)
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

void ALamp::SetLightColor_Implementation(const FLinearColor& Color)
{
	LightSource->SetLightColor(Color);
}

void ALamp::ToggleLamp_Implementation()
{
	if (bTurnedOn)
	{
		LightSource->SetIntensity(5000);
	}
	else
	{
		if (HasAuthority())
		{
			UE_LOG(LogTemp, Warning, TEXT("S off"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("C off"));
		}
		LightSource->SetIntensity(0);
	}
}