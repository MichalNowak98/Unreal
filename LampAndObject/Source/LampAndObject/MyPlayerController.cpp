// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"

AMyPlayerController::AMyPlayerController(const FObjectInitializer& ObjectInitializer) : APlayerController(ObjectInitializer)
{
	bReplicates = true;
}


void AMyPlayerController::Actualize_bRed_Implementation(const int ID, const bool Value)
{
	if (Lamps.Contains(ID))
	{
		this->Lamps[ID].bRed = Value;
	}
	else
	{
		ColorCh temp;
		temp.bRed = Value;
		temp.bGreen = false;
		temp.bBlue = false;
		this->Lamps.Add(ID, temp);
	}
}

bool AMyPlayerController::Actualize_bRed_Validate(const int ID, const bool Value)
{
	return true;
}

void AMyPlayerController::Actualize_bGreen_Implementation(const int ID, const bool Value)
{
	if (Lamps.Contains(ID))
	{
		this->Lamps[ID].bGreen = Value;
	}
	else
	{
		ColorCh temp;
		temp.bRed = false;
		temp.bGreen = Value;
		temp.bBlue = false;
		this->Lamps.Add(ID, temp);
	}
}

bool AMyPlayerController::Actualize_bGreen_Validate(const int ID, const bool Value)
{
	return true;
}

void AMyPlayerController::Actualize_bBlue_Implementation(const int ID, const bool Value)
{
	if (Lamps.Contains(ID))
	{
		this->Lamps[ID].bBlue = Value;
	}
	else
	{
		ColorCh temp;
		temp.bRed = false;
		temp.bGreen = false;
		temp.bBlue = Value;
		this->Lamps.Add(ID, temp);
	}
}

bool AMyPlayerController::Actualize_bBlue_Validate(const int ID, const bool Value)
{
	return true;
}

bool AMyPlayerController::Get_bBlue(const int ID)
{
	if (Lamps.Contains(ID))
	{
		return Lamps[ID].bBlue;
	}
	else
	{
		return false;
	}
}


void AMyPlayerController::Actualize_bDestructibleObject_Implementation(const int ID, const bool Value)
{
	if (DestructibleObjects.Contains(ID))
	{
		this->DestructibleObjects[ID] = Value;
	}
	this->DestructibleObjects.Add(ID, Value);
}

bool AMyPlayerController::Actualize_bDestructibleObject_Validate(const int ID, const bool Value)
{
	return true;
}

bool AMyPlayerController::Get_bRed(const int ID)
{
	if (Lamps.Contains(ID))
	{
		return Lamps[ID].bRed;
	}
	else
	{
		return false;
	}
}

bool AMyPlayerController::Get_bGreen(const int ID)
{
	if (Lamps.Contains(ID))
	{
		return Lamps[ID].bGreen;
	}
	else
	{
		return false;
	}
}

bool AMyPlayerController::Get_bIsIsDestroyed(const int ID)
{
	if (DestructibleObjects.Contains(ID))
	{
		return DestructibleObjects[ID];
	}
	else
	{
		return false;
	}
}