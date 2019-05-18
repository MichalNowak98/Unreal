// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestructibleComponent.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "MyPlayerController.h"
#include "Engine/World.h"
#include "UnrealNetwork.h"
#include "DestructibleObject.generated.h"

UCLASS()
class LAMPANDOBJECT_API ADestructibleObject : public AActor
{
	GENERATED_BODY()
	
public:	
	ADestructibleObject(const FObjectInitializer& ObjectInitializer);
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
		void Trigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(NetMulticast, Reliable)
		void Destroy(const float Damage, const FVector HitLocation, const FVector ImpulseDir, const float Impulse);
	UPROPERTY(EditAnywhere)
		class UDestructibleComponent* DestructibleComponent;
	static int NextID;
protected:
	virtual void BeginPlay() override;

private:
	AMyPlayerController* PlayerController;
	AActor* Player;

	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* TriggerComponent;

	UPROPERTY(replicated, VisibleAnywhere)
		int ID;
	UPROPERTY(replicated, VisibleAnywhere)
		FVector ImpulseDir;
	UPROPERTY(replicated, VisibleAnywhere)
		bool IsDestroyed;
	UPROPERTY(VisibleAnywhere)
		float MaxHealth;
	UPROPERTY(replicated, VisibleAnywhere)
		float CurrentHealth;
	UPROPERTY(VisibleAnywhere)
		float DefaultDamage;
	UPROPERTY(VisibleAnywhere)
		float DefaultImpulse;
};

int ADestructibleObject::NextID = 0;