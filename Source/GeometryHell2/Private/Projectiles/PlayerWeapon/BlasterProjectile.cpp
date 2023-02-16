// Geometry Hell 2. Made By Alexey Guchmazov

#include "Projectiles/PlayerWeapon/BlasterProjectile.h"
#include "Player/Emancipator.h"

void ABlasterProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!OtherActor)
	{
		Destroy();
		return;
	}
	
	if (OtherActor->GetClass()->IsChildOf(AEmancipator::StaticClass())) return;
	OtherActor->TakeDamage(BaseDamage, FDamageEvent{}, nullptr, nullptr);
	Destroy();
}