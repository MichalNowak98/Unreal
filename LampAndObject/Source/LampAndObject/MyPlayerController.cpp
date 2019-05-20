// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"

AMyPlayerController::AMyPlayerController(const FObjectInitializer& ObjectInitializer) : APlayerController(ObjectInitializer)
{
	bReplicates = true;
	if(GetWorld() && GetWorld()->GetGameState())
		GameState = Cast<AMyGameStateBase>(GetWorld()->GetGameState());
}


void AMyPlayerController::SteppedOnColorRed_Implementation(const int ID, const bool Value)
{
	if (GameState)
	{
		GameState->SteppedOnColorRed_Implementation(ID, Value);
	}
}

bool AMyPlayerController::SteppedOnColorRed_Validate(const int ID, const bool Value)
{
	return true;
}

void AMyPlayerController::SteppedOnColorGreen_Implementation(const int ID, const bool Value)
{
	if (GameState)
	{
		GameState->SteppedOnColorGreen_Implementation(ID, Value);
	}
}

bool AMyPlayerController::SteppedOnColorGreen_Validate(const int ID, const bool Value)
{
	return true;
}

void AMyPlayerController::SteppedOnColorBlue_Implementation(const int ID, const bool Value)
{
	if (GameState)
	{
		GameState->SteppedOnColorBlue_Implementation(ID, Value);
	}
}

bool AMyPlayerController::SteppedOnColorBlue_Validate(const int ID, const bool Value)
{
	return true;
}

void AMyPlayerController::Set_bToggleSwitch_Implementation(const int ID, const bool Value)
{
	if (GameState)
	{
		GameState->Set_bToggleSwitch_Implementation(ID, Value);
	}
}

bool AMyPlayerController::Set_bToggleSwitch_Validate(const int ID, const bool Value)
{
	return true;
}

void AMyPlayerController::Set_bDestructibleObject_Implementation(const int ID, const bool Value)
{
	if (GameState)
	{
		GameState->Set_bDestructibleObject_Implementation(ID, Value);
	}
}

bool AMyPlayerController::Set_bDestructibleObject_Validate(const int ID, const bool Value)
{
	return true;
}



int AMyPlayerController::Get_CountRedOn(const int ID)
{
	if (GameState)
	{
		return GameState->Get_CountRedOn(ID);
	}
	else
		return false;
}

int AMyPlayerController::Get_CountGreenOn(const int ID)
{
	if (GameState)
	{
		return GameState->Get_CountGreenOn(ID);
	}
	else
		return false;
}

int AMyPlayerController::Get_CountBlueOn(const int ID)
{
	if (GameState)
	{
		return GameState->Get_CountBlueOn(ID);
	}
	else
		return false;
}


bool AMyPlayerController::Get_bToggleSwitch(const int ID)
{
	if (GameState)
	{
		return GameState->Get_bToggleSwitch(ID);
	}
	else
		return true;
}
bool AMyPlayerController::Get_bIsIsDestroyed(const int ID)
{
	if (GameState)
	{
		return GameState->Get_bIsIsDestroyed(ID);
	}
	else
		return false;
}