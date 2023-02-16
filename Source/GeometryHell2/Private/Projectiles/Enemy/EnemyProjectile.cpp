// Geometry Hell 2. Made By Alexey Guchmazov

#include "Projectiles/Enemy/EnemyProjectile.h"
#include "Enemy/BaseEnemy.h"

void AEnemyProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!OtherActor)
	{
		Destroy();
		return;
	}
	
	if (OtherActor->GetClass()->IsChildOf(ABaseEnemy::StaticClass())) return;
	OtherActor->TakeDamage(BaseDamage, FDamageEvent{}, nullptr, nullptr);
	Destroy();
}
