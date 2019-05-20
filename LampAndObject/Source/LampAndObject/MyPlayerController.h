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

private:
	UPROPERTY()
		AMyGameStateBase* GameState;
};
