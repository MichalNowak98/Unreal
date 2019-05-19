// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameStateBase.h"

void AMyGameStateBase::Set_bColorRed_Implementation(const int ID, const bool Value)
{
	if (Lamps.Contains(ID))
	{
		if(Value)
			Lamps[ID].CountRedOn++;
		else
			Lamps[ID].CountRedOn--;
	}
	else
	{
		LampData temp;
		if (Value)
			temp.CountRedOn = 1;
		else
			temp.CountRedOn = 0;
		temp.CountGreenOn = 0;
		temp.CountBlueOn = 0;
		temp.bToggleSwitch = true;
		Lamps.Add(ID, temp);
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
		if (Value)
			Lamps[ID].CountGreenOn++;
		else
			Lamps[ID].CountGreenOn--;
	}
	else
	{
		LampData temp;
		temp.CountRedOn = 0;
		if (Value)
			temp.CountGreenOn = 1;
		else
			temp.CountGreenOn = 0;
		temp.CountBlueOn = 0;
		temp.bToggleSwitch = true;
		Lamps.Add(ID, temp);
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
		if (Value)
			Lamps[ID].CountBlueOn++;
		else
			Lamps[ID].CountBlueOn--;
	}
	else
	{
		LampData temp;
		temp.CountRedOn = 0;
		temp.CountGreenOn = 0;
		if (Value)
			temp.CountBlueOn = 1;
		else
			temp.CountBlueOn = 0;
		temp.bToggleSwitch = true;
		Lamps.Add(ID, temp);
	}
}

bool AMyGameStateBase::Set_bColorBlue_Validate(const int ID, const bool Value)
{
	return true;
}



void AMyGameStateBase::Set_bToggleSwitch_Implementation(const int ID, const bool Value)
{
	if (Lamps.Contains(ID))
	{
		Lamps[ID].bToggleSwitch = Value;
	}
	else
	{
		LampData temp;
		temp.CountRedOn = 0;
		temp.CountGreenOn = 0;
		temp.CountBlueOn = 0;
		temp.bToggleSwitch = Value;
		Lamps.Add(ID, temp);
	}
}

bool AMyGameStateBase::Set_bToggleSwitch_Validate(const int ID, const bool Value)
{
	return true;
}

void AMyGameStateBase::Set_bDestructibleObject_Implementation(const int ID, const bool Value)
{
	if (DestructibleObjects.Contains(ID))
	{
		DestructibleObjects[ID] = Value;
	}
	DestructibleObjects.Add(ID, Value);
}

bool AMyGameStateBase::Set_bDestructibleObject_Validate(const int ID, const bool Value)
{
	return true;
}

int AMyGameStateBase::Get_bRed(const int ID)
{
	if (Lamps.Contains(ID))
	{
		return Lamps[ID].CountRedOn;
	}
	else
	{
		return 0;
	}
}

int AMyGameStateBase::Get_bGreen(const int ID)
{
	if (Lamps.Contains(ID))
	{
		return Lamps[ID].CountGreenOn;
	}
	else
	{
		return 0;
	}
}

int AMyGameStateBase::Get_bBlue(const int ID)
{
	if (Lamps.Contains(ID))
	{
		return Lamps[ID].CountBlueOn;
	}
	else
	{
		return 0;
	}
}

bool AMyGameStateBase::Get_bToggleSwitch(const int ID)
{
	if (Lamps.Contains(ID))
	{
		return Lamps[ID].bToggleSwitch;
	}
	else
	{
		return true;
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