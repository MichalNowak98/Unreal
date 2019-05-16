// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/TriggerVolume.h"
#include "MyPlayerController.h"
#include "Components/BoxComponent.h"
#include "Runtime/Engine/Classes/Components/PointLightComponent.h"
#include "Runtime/Core/Public/Math/Color.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Lamp.generated.h"

UENUM()
enum class EColor
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

	void Color_on(EColor Ecolor);
	void Color_off(EColor Ecolor);
	UFUNCTION(NetMulticast, Reliable)
		void SetLightColor(const FLinearColor& Color);
	void SetLightColor_Implementation(const FLinearColor& Color);

	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* TriggerVolumeRed;
	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* TriggerVolumeGreen;
	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* TriggerVolumeBlue;
	UFUNCTION()
		void TriggerRed(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void TriggerGreen(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void TriggerBlue(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void TriggerRedEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
		void TriggerGreenEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
		void TriggerBlueEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	AActor* Player;
	AMyPlayerController* PlayerController;
	class UPointLightComponent* LightSource;
	FLinearColor Color;
};
