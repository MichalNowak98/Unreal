// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Components/PointLightComponent.h"
#include "Engine/TriggerVolume.h"
#include "Runtime/Core/Public/Math/Color.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "MyPlayerController.h"
#include "Engine/World.h"
#include "UnrealNetwork.h"
#include "GameFramework/Actor.h"
#include "Lamp.generated.h"

UENUM()
enum class EColor : uint8
{
	White UMETA(DisplayName = "White"),
	Red UMETA(DisplayName = "Red"),
	Green UMETA(DisplayName = "Green"),
	Blue UMETA(DisplayName = "Blue")
};

UCLASS()
class LAMPANDOBJECT_API ALamp : public AActor
{
	GENERATED_BODY()

public:
	ALamp(const FObjectInitializer& ObjectInitializer);
	virtual void Tick(float DeltaTime) override;
	//turns lamp on and off
	void Toggle_Lamp();

	//sets values of given channels to 1 keeping other values unchanged (mixed colors possible).
	//R = G = B = 1 for "White"
	void Color_on(EColor Color);
	//sets values of given channels to 0
	void Color_off(EColor Color);

	UFUNCTION(NetMulticast, Reliable)
		void SetLightColor(const FLinearColor Color);
	void SetLightColor_Implementation(const FLinearColor Color);

	UFUNCTION(Server, Reliable, WithValidation)
		void increment_CountRed();
	void increment_CountRed_Implementation();
	bool increment_CountRed_Validate();
	UFUNCTION(Server, Reliable, WithValidation)
		void increment_CountGreen();
	void increment_CountGreen_Implementation();
	bool increment_CountGreen_Validate();
	UFUNCTION(Server, Reliable, WithValidation)
		void increment_CountBlue();
	void increment_CountBlue_Implementation();
	bool increment_CountBlue_Validate();
	UFUNCTION(Server, Reliable, WithValidation)
		void decrement_CountRed();
	void decrement_CountRed_Implementation();
	bool decrement_CountRed_Validate();
	UFUNCTION(Server, Reliable, WithValidation)
		void decrement_CountGreen();
	void decrement_CountGreen_Implementation();
	bool decrement_CountGreen_Validate();
	UFUNCTION(Server, Reliable, WithValidation)
		void decrement_CountBlue();
	void decrement_CountBlue_Implementation();
	bool decrement_CountBlue_Validate();
protected:
	virtual void BeginPlay() override;

private:
	AMyPlayerController* PlayerController;
	bool TriggerVolumeRedPushed;
	bool TriggerVolumeGreenPushed;
	bool TriggerVolumeBluePushed;
	UPROPERTY(Replicated)
		FLinearColor color;
	UPROPERTY(Replicated)
		int CountRed;
	UPROPERTY(Replicated)
		int CountGreen;
	UPROPERTY(Replicated)
		int CountBlue;
	class UPointLightComponent *LightSource;
	AActor *Player;

	//pointers to trigger volumes from level
	UPROPERTY(EditAnywhere)
		ATriggerVolume *TriggerVolumeRed;
	UPROPERTY(EditAnywhere)
		ATriggerVolume *TriggerVolumeGreen;
	UPROPERTY(EditAnywhere)
		ATriggerVolume *TriggerVolumeBlue;

};
