// Geometry Hell 2. Made By Alexey Guchmazov

#include "Pickups/AbilityStaminaPickup.h"
#include "GameFramework/Character.h"
#include "Player/Components/AbilityComponent.h"

bool AAbilityStaminaPickup::GivePickup(AActor* PlayerPawn)
{
	const auto PlayerCharacter = Cast<APawn>(PlayerPawn);

	auto AbilityComponent = PlayerCharacter->FindComponentByClass<UAbilityComponent>();

	if (!AbilityComponent)
	{
		return false;
	}

	return AbilityComponent->TryToAddAbilityStamina(AbilityStaminaRestore);
}