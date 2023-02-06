// Geometry Hell 2. Made By Alexey Guchmazov

#include "Pickups/CoresPickup.h"
#include "Logic/MainGameInstance.h"

bool ACoresPickup::GivePickup(AActor* PlayerPawn)
{
	auto GameInstance = Cast<UMainGameInstance>(GetGameInstance());
	GameInstance->AddCores(CoresAmount);
	return true;
}
