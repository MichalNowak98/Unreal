// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"

AMyPlayerController::AMyPlayerController(const FObjectInitializer& ObjectInitializer) : APlayerController(ObjectInitializer)
{
	bReplicates = true;
	if(GetWorld() && GetWorld()->GetGameState())
		GameState = Cast<AMyGameStateBase>(GetWorld()->GetGameState());
}


void AMyPlayerController::Set_bColorRed_Implementation(const int ID, const bool Value)
{
	if (GameState)
	{
		GameState->Set_bColorRed_Implementation(ID, Value);
	}
}

bool AMyPlayerController::Set_bColorRed_Validate(const int ID, const bool Value)
{
	return true;
}

void AMyPlayerController::Set_bColorGreen_Implementation(const int ID, const bool Value)
{
	if (GameState)
	{
		GameState->Set_bColorGreen_Implementation(ID, Value);
	}
}

bool AMyPlayerController::Set_bColorGreen_Validate(const int ID, const bool Value)
{
	return true;
}

void AMyPlayerController::Set_bColorBlue_Implementation(const int ID, const bool Value)
{
	if (GameState)
	{
		GameState->Set_bColorBlue_Implementation(ID, Value);
	}
}

bool AMyPlayerController::Set_bColorBlue_Validate(const int ID, const bool Value)
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



int AMyPlayerController::Get_bRed(const int ID)
{
	if (GameState)
	{
		return GameState->Get_bRed(ID);
	}
	else
		return false;
}

int AMyPlayerController::Get_bGreen(const int ID)
{
	if (GameState)
	{
		return GameState->Get_bGreen(ID);
	}
	else
		return false;
}

int AMyPlayerController::Get_bBlue(const int ID)
{
	if (GameState)
	{
		return GameState->Get_bBlue(ID);
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