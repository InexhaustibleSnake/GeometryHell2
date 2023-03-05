// Geometry Hell 2. Made By Alexey Guchmazov

#include "Pickups/HealthPickup.h"
#include "Player/Components/HealthComponent.h"
#include "GameFramework/Character.h"

bool AHealthPickup::GivePickup(AActor* PlayerPawn)
{
	APawn* Player = Cast<APawn>(PlayerPawn);
	
	if (!Player) return false;
	UHealthComponent* HealthComponent = Player->FindComponentByClass<UHealthComponent>();

	if (!HealthComponent)
	{
		return false;
	}

	return HealthComponent->TryToAddHealth(HealAmount);
}
