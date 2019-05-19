// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameStateBase.h"

void AMyGameStateBase::Set_bColorRed_Implementation(const int ID, const bool Value)
{
	if (Lamps.Contains(ID))
	{
		this->Lamps[ID].bRedOn = Value;
	}
	else
	{
		ColorCh temp;
		temp.bRedOn = Value;
		temp.bGreenOn = false;
		temp.bBlueOn = false;
		this->Lamps.Add(ID, temp);
	}
}

bool AMyGameStateBase::Set_bColorRed_Validate(const int ID, const bool Value)
{
	return true;
}

void AMyGameStateBase::Set_bColorGreen_Implementation(const int ID, const bool Value)
{
	if (Lamps.Contains(ID))
	{
		this->Lamps[ID].bGreenOn = Value;
	}
	else
	{
		ColorCh temp;
		temp.bRedOn = false;
		temp.bGreenOn = Value;
		temp.bBlueOn = false;
		this->Lamps.Add(ID, temp);
	}
}

bool AMyGameStateBase::Set_bColorGreen_Validate(const int ID, const bool Value)
{
	return true;
}

void AMyGameStateBase::Set_bColorBlue_Implementation(const int ID, const bool Value)
{
	if (Lamps.Contains(ID))
	{
		this->Lamps[ID].bBlueOn = Value;
	}
	else
	{
		ColorCh temp;
		temp.bRedOn = false;
		temp.bGreenOn = false;
		temp.bBlueOn = Value;
		this->Lamps.Add(ID, temp);
	}
}

bool AMyGameStateBase::Set_bColorBlue_Validate(const int ID, const bool Value)
{
	return true;
}



void AMyGameStateBase::Set_bDestructibleObject_Implementation(const int ID, const bool Value)
{
	if (DestructibleObjects.Contains(ID))
	{
		this->DestructibleObjects[ID] = Value;
	}
	this->DestructibleObjects.Add(ID, Value);
}

bool AMyGameStateBase::Set_bDestructibleObject_Validate(const int ID, const bool Value)
{
	return true;
}

bool AMyGameStateBase::Get_bRed(const int ID)
{
	if (Lamps.Contains(ID))
	{
		return Lamps[ID].bRedOn;
	}
	else
	{
		return false;
	}
}

bool AMyGameStateBase::Get_bGreen(const int ID)
{
	if (Lamps.Contains(ID))
	{
		return Lamps[ID].bGreenOn;
	}
	else
	{
		return false;
	}
}

bool AMyGameStateBase::Get_bBlue(const int ID)
{
	if (Lamps.Contains(ID))
	{
		return Lamps[ID].bBlueOn;
	}
	else
	{
		return false;
	}
}

bool AMyGameStateBase::Get_bIsIsDestroyed(const int ID)
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