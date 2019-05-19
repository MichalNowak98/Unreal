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

	//ID for next lamp (given at BeginPlay)
	static int NextID;	

protected:
	virtual void BeginPlay() override;
	//sets channel represened by EColor to 1
	void Color_on(EColor Ecolor, FLinearColor& Color);
	//sets channel represened by EColor to 0
	void Color_off(EColor Ecolor, FLinearColor& Color);
	//sets color on server and all clients
	UFUNCTION(NetMulticast, Reliable)
		void SetLightColor(const FLinearColor& Color);
	void SetLightColor_Implementation(const FLinearColor& Color);

	UFUNCTION(NetMulticast, Reliable)
		void ToggleLamp();
	void ToggleLamp_Implementation();
	
	//callbacks, set color on and off depending on UBoxComponents delegate callbacks
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
	UFUNCTION()
		void ToggleSwitchCallback(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	///variables///
	UPROPERTY(replicated, VisibleAnywhere)
		int ID;
	AActor* Player;
	AMyPlayerController* PlayerController;
	UPointLightComponent* LightSource;

private:

	UPROPERTY(VisibleAnywhere)
		UBoxComponent* TriggerVolumeRed;
	UPROPERTY(VisibleAnywhere)
		UBoxComponent* TriggerVolumeGreen;
	UPROPERTY(VisibleAnywhere)
		UBoxComponent* TriggerVolumeBlue;
	UPROPERTY(VisibleAnywhere)
		UBoxComponent* ToggleSwitch;
	UPROPERTY(replicated, VisibleAnywhere)
		bool bTurnedOn;
};

int ALamp::NextID = 0;