// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MyGameStateBase.generated.h"

struct LampData
{
	int CountRedOn;
	int CountGreenOn;
	int CountBlueOn;
	bool bToggleSwitch;
};

UCLASS()
class LAMPANDOBJECT_API AMyGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
private:
	TMap<int, LampData> Lamps;
	TMap<int, bool> DestructibleObjects;
public:
	UFUNCTION(Server, Reliable, WithValidation)
		void SteppedOnColorRed(const int ID, const bool Value);
	void SteppedOnColorRed_Implementation(const int ID, const bool Value);
	bool SteppedOnColorRed_Validate(const int ID, const bool Value);

	UFUNCTION(Server, Reliable, WithValidation)
		void SteppedOnColorGreen(const int ID, const bool Value);
	void SteppedOnColorGreen_Implementation(const int ID, const bool Value);
	bool SteppedOnColorGreen_Validate(const int ID, const bool Value);

	UFUNCTION(Server, Reliable, WithValidation)
		void SteppedOnColorBlue(const int ID, const bool Value);
	void SteppedOnColorBlue_Implementation(const int ID, const bool Value);
	bool SteppedOnColorBlue_Validate(const int ID, const bool Value);

	UFUNCTION(Server, Reliable, WithValidation)
		void Set_bToggleSwitch(const int ID, const bool Value);
	void Set_bToggleSwitch_Implementation(const int ID, const bool Value);
	bool Set_bToggleSwitch_Validate(const int ID, const bool Value);

	UFUNCTION(Server, Reliable, WithValidation)
		void Set_bDestructibleObject(const int ID, const bool Value);
	void Set_bDestructibleObject_Implementation(const int ID, const bool Value);
	bool Set_bDestructibleObject_Validate(const int ID, const bool Value);
	
	//get funtions
	int Get_CountRedOn(const int ID);
	int Get_CountGreenOn(const int ID);
	int Get_CountBlueOn(const int ID);
	bool Get_bToggleSwitch(const int ID);
	bool Get_bIsIsDestroyed(const int ID);
};
