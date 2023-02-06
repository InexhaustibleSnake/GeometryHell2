// Geometry Hell 2. Made By Alexey Guchmazov

#pragma once

#include "CoreMinimal.h"
#include "Pickups/BasePickup.h"
#include "CoresPickup.generated.h"

UCLASS()
class GEOMETRYHELL2_API ACoresPickup : public ABasePickup
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cores")
		float CoresAmount = 25.0f;

	virtual bool GivePickup(AActor* PlayerPawn) override;
};
