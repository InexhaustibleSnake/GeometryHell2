// Geometry Hell 2. Made By Alexey Guchmazov

#include "Pickups/AbilityStaminaPickup.h"
#include "GameFramework/Character.h"
#include "Player/Emancipator.h"
#include "Player/Components/AbilityComponent.h"

bool AAbilityStaminaPickup::GivePickup(AActor* PlayerPawn)
{
	const auto PlayerCharacter = Cast<AEmancipator>(PlayerPawn);

	if (!PlayerPawn->GetClass()->IsChildOf(AEmancipator::StaticClass()))
	{
		return false;
	}

	auto AbilityComponent = PlayerCharacter->FindComponentByClass<UAbilityComponent>();

	return AbilityComponent->TryToAddAbilityStamina(AbilityStaminaRestore) ? true : false;
}