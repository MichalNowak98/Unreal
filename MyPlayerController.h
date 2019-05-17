#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

struct ColorCh
{
	bool bRed;
	bool bGreen;
	bool bBlue;
};

UCLASS()
class LAMPANDOBJECT_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	//replication not default?
	AMyPlayerController(const FObjectInitializer& ObjectInitializer);

	TMap<int, ColorCh> Lamps;

	//server set funcions
	UFUNCTION(Server, Reliable, WithValidation)
		void Actualize_bRed(const int ID, const bool Value);
	void Actualize_bRed_Implementation(const int ID, const bool Value);
	bool Actualize_bRed_Validate(const int ID, const bool Value);

	UFUNCTION(Server, Reliable, WithValidation)
		void Actualize_bGreen(const int ID, const bool Value);
	void Actualize_bGreen_Implementation(const int ID, const bool Value);
	bool Actualize_bGreen_Validate(const int ID, const bool Value);

	UFUNCTION(Server, Reliable, WithValidation)
		void Actualize_bBlue(const int ID, const bool Value);
	void Actualize_bBlue_Implementation(const int ID, const bool Value);
	bool Actualize_bBlue_Validate(const int ID, const bool Value);

	//get funtions
	bool Get_bRed(const int ID);
	bool Get_bGreen(const int ID);
	bool Get_bBlue(const int ID);
};
