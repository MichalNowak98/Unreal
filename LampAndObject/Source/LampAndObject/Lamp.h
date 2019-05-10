// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Components/PointLightComponent.h"
#include "Engine/TriggerVolume.h"
#include "Runtime/Core/Public/Math/Color.h"
#include "GameFramework/Actor.h"
#include "Lamp.generated.h"

UCLASS()
class LAMPANDOBJECT_API ALamp : public AActor
{
	GENERATED_BODY()
	
public:	
	ALamp();
	virtual void Tick(float DeltaTime) override;
	//turns lamp on and off
	void Toggle_Lamp();

	enum EColor { White, Red, Green, Blue };
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
		class UPointLightComponent *LightSource;
	AActor *Player;

	//pointers to trigger volumes from level
	UPROPERTY(EditAnywhere)
		ATriggerVolume *TriggerVolumeRed;
	UPROPERTY(EditAnywhere)
		ATriggerVolume *TriggerVolumeGreen;
	UPROPERTY(EditAnywhere)
		ATriggerVolume *TriggerVolumeBlue;

	//sets values of given channels to 1 keeping other values unchanged (mixed colors possible).
	//R = G = B = 1 for "White"
	void Color_on(EColor Color);

	//sets values of given channels to 0
	void Color_off(EColor Color);
};
