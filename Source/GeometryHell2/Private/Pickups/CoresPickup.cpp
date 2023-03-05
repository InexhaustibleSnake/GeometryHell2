// Geometry Hell 2. Made By Alexey Guchmazov

#include "Pickups/CoresPickup.h"
#include "Logic/MainGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

bool ACoresPickup::GivePickup(AActor* PlayerPawn)
{
	if (!PlayerPawn->GetClass()->IsChildOf(ACharacter::StaticClass()))
	{
		return false;
	}

	auto GameInstance = Cast<UMainGameInstance>(GetGameInstance());

	GameInstance->AddCores(CoresAmount);

	OnPickupTaked.Broadcast();

	return true;
}
