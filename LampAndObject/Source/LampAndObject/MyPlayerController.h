#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyGameStateBase.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "MyPlayerController.generated.h"

UCLASS()
class LAMPANDOBJECT_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	//replication not default?
	AMyPlayerController(const FObjectInitializer& ObjectInitializer);

	//server set funcions
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
		void Set_bToggleSwitch(const int ID, const bool Value);
	void Set_bToggleSwitch_Implementation(const int ID, const bool Value);
	bool Set_bToggleSwitch_Validate(const int ID, const bool Value);

	UFUNCTION(Server, Reliable, WithValidation)
		void Set_bDestructibleObject(const int ID, const bool Value);
	void Set_bDestructibleObject_Implementation(const int ID, const bool Value);
	bool Set_bDestructibleObject_Validate(const int ID, const bool Value);

	//get funtions
	int Get_bRed(const int ID);
	int Get_bGreen(const int ID);
	int Get_bBlue(const int ID);
	bool Get_bToggleSwitch(const int ID);
	bool Get_bIsIsDestroyed(const int ID);

private:
	UPROPERTY()
		AMyGameStateBase* GameState;
};
