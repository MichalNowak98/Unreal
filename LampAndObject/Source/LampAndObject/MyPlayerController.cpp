// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"

AMyPlayerController::AMyPlayerController(const FObjectInitializer& ObjectInitializer) : APlayerController(ObjectInitializer)
{
	bReplicates = true;
	this->bRed = this->bGreen = this->bBlue = false;
}

void AMyPlayerController::Actualize_bRed_Implementation(const bool Value)
{
	this->bRed = Value;
}

bool AMyPlayerController::Actualize_bRed_Validate(const bool Value)
{
	return true;
}

void AMyPlayerController::Actualize_bGreen_Implementation(const bool Value)
{
	this->bGreen = Value;
}

bool AMyPlayerController::Actualize_bGreen_Validate(const bool Value)
{
	return true;
}

void AMyPlayerController::Actualize_bBlue_Implementation(const bool Value)
{
	this->bBlue = Value;
}

bool AMyPlayerController::Actualize_bBlue_Validate(const bool Value)
{
	return true;
}

bool AMyPlayerController::Get_bBlue()
{
	return bBlue;
}

bool AMyPlayerController::Get_bRed()
{
	return bRed;
}

bool AMyPlayerController::Get_bGreen()
{
	return bGreen;
}
