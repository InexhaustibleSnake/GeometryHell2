// Geometry Hell 2. Made By Alexey Guchmazov

#pragma once

#include "CoreMinimal.h"
#include "Pickups/BasePickup.h"
#include "AbilityStaminaPickup.generated.h"

UCLASS()
class GEOMETRYHELL2_API AAbilityStaminaPickup : public ABasePickup
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cores")
		float AbilityStaminaRestore = 5.0f;

	virtual bool GivePickup(AActor* PlayerPawn) override;
};
