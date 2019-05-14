#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

UCLASS()
class LAMPANDOBJECT_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	//replication not default?
	AMyPlayerController(const FObjectInitializer& ObjectInitializer);
	
	bool bRed;
	bool bGreen;
	bool bBlue;
	//server set funcions
	UFUNCTION(Server, Reliable, WithValidation)
		void Actualize_bRed(const bool Value);
	void Actualize_bRed_Implementation(const bool Value);
	bool Actualize_bRed_Validate(const bool Value);

	UFUNCTION(Server, Reliable, WithValidation)
		void Actualize_bGreen(const bool Value);
	void Actualize_bGreen_Implementation(const bool Value);
	bool Actualize_bGreen_Validate(const bool Value);

	UFUNCTION(Server, Reliable, WithValidation)
		void Actualize_bBlue(const bool Value);
	void Actualize_bBlue_Implementation(const bool Value);
	bool Actualize_bBlue_Validate(const bool Value);

	//get funtions
	bool Get_bRed();
	bool Get_bGreen();
	bool Get_bBlue();
};
