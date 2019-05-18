// Fill out your copyright notice in the Description page of Project Settings.


#include "DestructibleObject.h"

// Sets default values
ADestructibleObject::ADestructibleObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	TriggerComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Component"));
	TriggerComponent->SetupAttachment(RootComponent);

	bReplicates = true;
	bAlwaysRelevant = true;

	IsDestroyed = false;
	MaxHealth = 10.f;
	DefaultDamage = 10.f;
	DefaultImpulse = 10.f;
}

// Called when the game starts or when spawned
void ADestructibleObject::BeginPlay()
{
	Super::BeginPlay();
	if (DestructibleComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("there is something to destroy"));
		DestructibleComponent->SetNotifyRigidBodyCollision(true);
	}
	TriggerComponent->OnComponentBeginOverlap.AddDynamic(this, &ADestructibleObject::Trigger);
	CurrentHealth = MaxHealth;
}

// Called every frame
void ADestructibleObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Player = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void ADestructibleObject::Trigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsDestroyed && DestructibleComponent && OtherActor == Player)
	{
		UE_LOG(LogTemp, Warning, TEXT("Trigger worked"));
		Destroy(DefaultDamage, DestructibleComponent->GetComponentLocation(), OtherActor->GetActorForwardVector(), DefaultImpulse);
	}
}

void ADestructibleObject::Destroy_Implementation(const float Damage, const FVector HitLocation, const FVector ImpulseDir, const float Impulse)
{
	if (!IsDestroyed)
	{
		IsDestroyed = true;
		UE_LOG(LogTemp, Warning, TEXT("Destruction worked"));
		DestructibleComponent->ApplyDamage(Damage, HitLocation, ImpulseDir, Impulse);
	}
}