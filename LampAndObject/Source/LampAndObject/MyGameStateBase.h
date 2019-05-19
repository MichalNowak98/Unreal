// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MyGameStateBase.generated.h"

struct ColorCh
{
	bool bRedOn;
	bool bGreenOn;
	bool bBlueOn;
};

UCLASS()
class LAMPANDOBJECT_API AMyGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
private:
	TMap<int, ColorCh> Lamps;
	TMap<int, bool> DestructibleObjects;
public:
	UFUNCTION(Server, Reliable, WithValidation)
		void Set_bColorRed(const int ID, const bool Value);
	void Set_bColorRed_Implementation(const int ID, const bool Value);
	bool Set_bColorRed_Validate(const int ID, const bool Value);

	UFUNCTION(Server, Reliable, WithValidation)
		void Set_bColorGreen(const int ID, const bool Value);
	void Set_bColorGreen_Implementation(const int ID, const bool Value);
	bool Set_bColorGreen_Validate(const int ID, const bool Value);

	UFUNCTION(Server, Reliable, WithValidation)
		void Set_bColorBlue(const int ID, const bool Value);
	void Set_bColorBlue_Implementation(const int ID, const bool Value);
	bool Set_bColorBlue_Validate(const int ID, const bool Value);

	UFUNCTION(Server, Reliable, WithValidation)
		void Set_bDestructibleObject(const int ID, const bool Value);
	void Set_bDestructibleObject_Implementation(const int ID, const bool Value);
	bool Set_bDestructibleObject_Validate(const int ID, const bool Value);
	
	//get funtions
	bool Get_bRed(const int ID);
	bool Get_bGreen(const int ID);
	bool Get_bBlue(const int ID);
	bool Get_bIsIsDestroyed(const int ID);
};