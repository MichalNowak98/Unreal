// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/TriggerVolume.h"
#include "MyPlayerController.h"
#include "Runtime/Engine/Classes/Components/PointLightComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Lamp.generated.h"

UCLASS()
class LAMPANDOBJECT_API ALamp : public AActor
{
	GENERATED_BODY()
	
public:
	ALamp(const FObjectInitializer& ObjectInitializer);
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	AActor* Player;
	AMyPlayerController* PlayerController;
	class UPointLightComponent* LightSource;
	UPROPERTY(EditAnywhere)
		ATriggerVolume* TriggerVolumeRed;
	UPROPERTY(EditAnywhere)
		ATriggerVolume* TriggerVolumeGreen;
	UPROPERTY(EditAnywhere)
		ATriggerVolume* TriggerVolumeBlue;

};
