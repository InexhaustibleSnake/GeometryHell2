// Geometry Hell 2. Made By Alexey Guchmazov

#include "Pickups/BasePickup.h"
#include "Components/SphereComponent.h"

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

bool ABasePickup::GivePickup(AActor* PlayerPawn)
{
	return false;
}

void ABasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (GivePickup(OtherActor))
	{
		Destroy();
	}
}

void ABasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(FRotator(0.0f, 1.0f, 0.0f));
}

