// Geometry Hell 2. Made By Alexey Guchmazov


#include "Weapon/BlasterWeapon.h"
#include "Projectiles/BaseProjectile.h"

void ABlasterWeapon::MakeShot()
{
	if (!CanFire) return;

	FVector TraceStart, TraceEnd;

	GetTraceData(TraceStart, TraceEnd);

	FHitResult HitResult;

	MakeTrace(HitResult, TraceStart, TraceEnd);

	const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
	const FVector Direction = (EndPoint - GetMuzzleWorldLocation()).GetSafeNormal();
	const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
	ABaseProjectile* Projectile = GetWorld()->SpawnActorDeferred<ABaseProjectile>(ProjectileToSpawn, SpawnTransform);
	if (Projectile)
	{
		CanFire = false;

		Projectile->SetOwner(GetOwner());
		Projectile->SetShotDirection(Direction);
		Projectile->SetDamage(GetOwner()->CustomTimeDilation > 1.0f ? ProjectileDamage * 1.5 : ProjectileDamage);
		Projectile->FinishSpawning(SpawnTransform);

		GetWorldTimerManager().SetTimer(DelayTimer, this, &ABaseWeapon::ControlFireDelay, FireRate, false);
	}

}
