// Geometry Hell 2. Made By Alexey Guchmazov

#pragma once

#include "CoreMinimal.h"
#include "Pickups/BasePickup.h"
#include "HealthPickup.generated.h"

UCLASS()
class GEOMETRYHELL2_API AHealthPickup : public ABasePickup
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Heal")
		float HealAmount = 25.0f;

	virtual bool GivePickup(AActor* PlayerPawn) override;
};
