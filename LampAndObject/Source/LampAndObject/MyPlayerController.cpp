// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"

AMyPlayerController::AMyPlayerController() : APlayerController()
{
	CountRed = CountGreen = CountBlue = 0;
}

void AMyPlayerController::Server_Set_CountRed_Implementation(const int & _CountRed)
{
	CountRed = _CountRed;
}

bool AMyPlayerController::Server_Set_CountRed_Validate(const int & _CountRed)
{
	return true;
}

void AMyPlayerController::Server_Set_CountGreen_Implementation(const int & _CountGreen)
{
	CountGreen = _CountGreen;
}

bool AMyPlayerController::Server_Set_CountGreen_Validate(const int & _CountGreen)
{
	return true;
}

void AMyPlayerController::Server_Set_CountBlue_Implementation(const int & _CountBlue)
{
	CountBlue = _CountBlue;
}

bool AMyPlayerController::Server_Set_CountBlue_Validate(const int & _CountBlue)
{
	return true;
}

int AMyPlayerController::Server_Get_CountRed()
{
	return CountRed;
}

int AMyPlayerController::Server_Get_CountGreen()
{
	return CountGreen;
}

int AMyPlayerController::Server_Get_CountBlue()
{
	return CountBlue;
}