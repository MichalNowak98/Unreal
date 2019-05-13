// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class LAMPANDOBJECT_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	int CountRed;
	int CountGreen;
	int CountBlue;
public:
	AMyPlayerController();
	//server functions
	UFUNCTION(Server, Reliable, WithValidation)
		void Server_Set_CountRed(const int &_CountRed);
	void Server_Set_CountRed_Implementation(const int &_CountRed);
	bool Server_Set_CountRed_Validate(const int &_CountRed);
	UFUNCTION(Server, Reliable, WithValidation)
		void Server_Set_CountGreen(const int &_CountGreen);
	void Server_Set_CountGreen_Implementation(const int &_CountGreen);
	bool Server_Set_CountGreen_Validate(const int &_CountGreen);
	UFUNCTION(Server, Reliable, WithValidation)
		void Server_Set_CountBlue(const int &_CountBlue);
	void Server_Set_CountBlue_Implementation(const int &_CountBlue);
	bool Server_Set_CountBlue_Validate(const int &_CountBlue);

	static int Server_Get_CountRed();
	static int Server_Get_CountGreen();
	static int Server_Get_CountBlue();
};
