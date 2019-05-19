// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameModeBase.h"

AMyGameModeBase::AMyGameModeBase() : AGameModeBase()
{
	PlayerControllerClass = AMyPlayerController::StaticClass();
	GameStateClass = AMyGameStateBase::StaticClass();
}