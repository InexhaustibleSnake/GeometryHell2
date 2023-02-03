// Geometry Hell 2. Made By Alexey Guchmazov

#include "Pickups/HealthPickup.h"
#include "Kismet/GameplayStatics.h"
#include "Player/Components/HealthComponent.h"
#include "GameFramework/Character.h"

bool AHealthPickup::GivePickup(AActor* PlayerPawn)
{
	ACharacter* Player = Cast<ACharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
	if (!Player) return false;
	UHealthComponent* HealthComponent = Player->FindComponentByClass<UHealthComponent>();

	if (PlayerPawn != Player)
	{
		return false;
	}

	return HealthComponent->TryToAddHealth(HealAmount);
}
