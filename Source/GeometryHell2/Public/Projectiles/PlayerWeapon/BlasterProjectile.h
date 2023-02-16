// Geometry Hell 2. Made By Alexey Guchmazov

#pragma once

#include "CoreMinimal.h"
#include "Projectiles/BaseProjectile.h"
#include "BlasterProjectile.generated.h"


UCLASS()
class GEOMETRYHELL2_API ABlasterProjectile : public ABaseProjectile
{
	GENERATED_BODY()

protected:
	
	void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
