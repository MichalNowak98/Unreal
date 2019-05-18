// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestructibleComponent.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "Engine/World.h"
#include "DestructibleObject.generated.h"

UCLASS()
class LAMPANDOBJECT_API ADestructibleObject : public AActor
{
	GENERATED_BODY()
	
public:	
	ADestructibleObject();
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
		void Trigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void Destroy(float Damage, FVector HitLocation, FVector ImpulseDir, float Impulse);
	UPROPERTY(EditAnywhere)
		class UDestructibleComponent* DestructibleComponent;
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* TriggerComponent;

	AActor* Player;
	UPROPERTY(VisibleAnywhere)
		bool IsDestroyed;
	UPROPERTY(VisibleAnywhere)
		float MaxHealth;
	UPROPERTY(VisibleAnywhere)
		float CurrentHealth;
	UPROPERTY(VisibleAnywhere)
		float DefaultDamage;
	UPROPERTY(VisibleAnywhere)
		float DefaultImpulse;
};
