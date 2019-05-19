// Fill out your copyright notice in the Description page of Project Settings.


#include "DestructibleObject.h"

ADestructibleObject::ADestructibleObject(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	TriggerComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Component"));
	TriggerComponent->SetupAttachment(RootComponent);

	bReplicates = true;
	bAlwaysRelevant = true;

	ADestructibleObject::NextID = 1;

	IsDestroyed = false;
	MaxHealth = 10.f;
	DefaultDamage = 10.f;
	DefaultImpulse = 10.f;
}


void ADestructibleObject::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ADestructibleObject, ID);
	//DOREPLIFETIME(ADestructibleObject, IsDestroyed);
	DOREPLIFETIME(ADestructibleObject, CurrentHealth); 
	DOREPLIFETIME(ADestructibleObject, DestructorImpulseDir);
}


void ADestructibleObject::BeginPlay()
{
	Super::BeginPlay();
	if (DestructibleComponent)
	{
		DestructibleComponent->SetNotifyRigidBodyCollision(true);
	}
	TriggerComponent->OnComponentBeginOverlap.AddDynamic(this, &ADestructibleObject::Trigger);
	if (IsDestroyed)
	{
		UE_LOG(LogTemp, Warning, TEXT("Should be destoryed on start"));
		Destroy(DefaultDamage, DestructibleComponent->GetComponentLocation(), DestructorImpulseDir, DefaultImpulse);
	}
	else
		CurrentHealth = MaxHealth;
	if (HasAuthority())
	{
		ID = ADestructibleObject::NextID;
		ADestructibleObject::NextID++;
	}
	PlayerController = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());
	Player = GetWorld()->GetFirstPlayerController()->GetPawn();
}

// Called every frame
void ADestructibleObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (HasAuthority())
	{
		//int CountOfDestroyedObject = 0;
		//for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
		//{
		//	if (Iterator->IsValid())
		//	{
		//		AMyPlayerController* temp = Cast<AMyPlayerController>(Iterator->Get());
		//		CountOfDestroyedObject += temp->Get_bIsIsDestroyed(ID);
		//		if (temp->Get_bIsIsDestroyed(ID))
		//		{	//direction of destructor. Every Client gets similar explosion
		//			DestructorImpulseDir = temp->GetPawn()->GetActorForwardVector();
		//		}
		//	}
		//}
		//if (CountOfDestroyedObject > 0)
		//{
		//	Destroy(DefaultDamage, DestructibleComponent->GetComponentLocation(), DestructorImpulseDir, DefaultImpulse);
		//}
		if (PlayerController && PlayerController->Get_bIsIsDestroyed(ID) && !IsDestroyed)
		{

			Destroy(DefaultDamage, DestructibleComponent->GetComponentLocation(), PlayerController->GetPawn()->GetActorForwardVector(), DefaultImpulse);
		}
	}
	else
	{
		PlayerController->Set_bDestructibleObject(ID, IsDestroyed);
	}
}

void ADestructibleObject::Trigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsDestroyed && DestructibleComponent && OtherActor == Player)
	{
		DestructorImpulseDir = OtherActor->GetActorForwardVector();
		Destroy(DefaultDamage, DestructibleComponent->GetComponentLocation(), DestructorImpulseDir, DefaultImpulse);
	}
}

void ADestructibleObject::Destroy_Implementation(const float Damage, const FVector HitLocation, const FVector ImpulseDir, const float Impulse)
{
	if (!IsDestroyed)
	{
		IsDestroyed = true;
		CurrentHealth = 0;
		DestructibleComponent->ApplyDamage(Damage, HitLocation, ImpulseDir, Impulse);
	}
}