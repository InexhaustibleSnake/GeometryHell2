// Geometry Hell 2. Made By Alexey Guchmazov

#pragma once

#include "CoreMinimal.h"
#include "Projectiles/BaseProjectile.h"
#include "EnemyProjectile.generated.h"

UCLASS()
class GEOMETRYHELL2_API AEnemyProjectile : public ABaseProjectile
{
	GENERATED_BODY()

protected:

	virtual void OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit) override;
};
