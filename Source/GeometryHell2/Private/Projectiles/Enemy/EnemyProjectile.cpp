// Geometry Hell 2. Made By Alexey Guchmazov

#include "Projectiles/Enemy/EnemyProjectile.h"
#include "Enemy/BaseEnemy.h"

void AEnemyProjectile::OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	if (OtherActor->IsA(ABaseEnemy::StaticClass())) return;
	OtherActor->TakeDamage(BaseDamage, FDamageEvent{}, nullptr, nullptr);
	Destroy();
}
