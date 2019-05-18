// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UnrealNetwork.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "MyPlayerController.h"
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

	void Color_on(EColor Ecolor, FLinearColor& Color);
	void Color_off(EColor Ecolor, FLinearColor& Color);
	UFUNCTION(NetMulticast, Reliable)
		void SetLightColor(const FLinearColor& Color);
	void SetLightColor_Implementation(const FLinearColor& Color);

	static int NextID;
	UFUNCTION()
		void TriggerRedOn(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void TriggerGreenOn(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void TriggerBlueOn(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void TriggerRedOff(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
		void TriggerGreenOff(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
		void TriggerBlueOff(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(replicated, VisibleAnywhere)
		int ID;
	AActor* Player;
	AMyPlayerController* PlayerController;
	class UPointLightComponent* LightSource;
	UPROPERTY(EditAnywhere)
		class UBoxComponent* TriggerVolumeRed;
	UPROPERTY(EditAnywhere)
		class UBoxComponent* TriggerVolumeGreen;
	UPROPERTY(EditAnywhere)
		class UBoxComponent* TriggerVolumeBlue;
};

int ALamp::NextID = 0;