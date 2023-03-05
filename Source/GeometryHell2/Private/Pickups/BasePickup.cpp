// Geometry Hell 2. Made By Alexey Guchmazov

#include "Pickups/BasePickup.h"
#include "Components/SphereComponent.h"
#include "Player/Emancipator.h"

ABasePickup::ABasePickup()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->SetupAttachment(GetRootComponent());

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(SphereComponent);
}

void ABasePickup::BeginPlay()
{
	Super::BeginPlay();
}

void ABasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(FRotator(0.0f, 1.0f, 0.0f));
}

bool ABasePickup::GivePickup(AActor* PlayerPawn)
{
	return false;
}

void ABasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (!OtherActor->GetClass()->IsChildOf(AEmancipator::StaticClass())) return;

	if (GivePickup(OtherActor))
	{
		ShouldRespawn ? PickupTaken() : Destroy();
	}
}

void ABasePickup::PickupTaken()
{
	if (GetRootComponent())
	{
		GetRootComponent()->SetVisibility(false, true);
	}

	SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	GetWorldTimerManager().SetTimer(RespawnTimer, this, &ABasePickup::RespawnPickup, RespawnTime);
}

void ABasePickup::RespawnPickup()
{
	if (GetRootComponent())
	{
		GetRootComponent()->SetVisibility(true, true);
	}

	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}
