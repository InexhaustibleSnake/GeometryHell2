// Geometry Hell 2. Made By Alexey Guchmazov

#include "Pickups/HealthPickup.h"
#include "Kismet/GameplayStatics.h"
#include "Player/Components/HealthComponent.h"
#include "GameFramework/Character.h"

bool AHealthPickup::GivePickup(AActor* PlayerPawn)
{
	APawn* Player = Cast<APawn>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
	if (!Player) return false;
	UHealthComponent* HealthComponent = Player->FindComponentByClass<UHealthComponent>();

	if (!PlayerPawn->GetClass()->IsChildOf(ACharacter::StaticClass()))
	{
		return false;
	}

	return HealthComponent->TryToAddHealth(HealAmount);
}
