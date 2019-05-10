#pragma once
#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Components/PointLightComponent.h"
#include "Engine/TriggerVolume.h"
#include "GameFramework/Actor.h"
#include "Lamp.generated.h"

enum EColor { Red, Green, Blue };

UCLASS()
class LAMPANDOBJECT_API ALamp : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALamp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
		class UPointLightComponent *LightSource;
	AActor *Player;

	UPROPERTY(EditAnywhere)
		ATriggerVolume *PressurePlate;
};
