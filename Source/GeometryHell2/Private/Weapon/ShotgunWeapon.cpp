// Geometry Hell 2. Made By Alexey Guchmazov


#include "Weapon/ShotgunWeapon.h"
#include "Projectiles/BaseProjectile.h"

void AShotgunWeapon::MakeShot()
{
	if (!CanFire) return;

	FVector TraceStart, TraceEnd;

	GetTraceData(TraceStart, TraceEnd);

	FHitResult HitResult;

	MakeTrace(HitResult, TraceStart, TraceEnd);

	const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
	FVector Direction = (EndPoint - GetMuzzleWorldLocation()).GetSafeNormal();
	const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());

	for (int NumberOfShots = 0; NumberOfShots < NumOfProjectiles; ++NumberOfShots)
	{
		ABaseProjectile* Projectile = GetWorld()->SpawnActorDeferred<ABaseProjectile>(ProjectileToSpawn, SpawnTransform);
		if (Projectile)
		{
			CanFire = false;
			if (GetOwner()->CustomTimeDilation > 1.0f)
			{
				Projectile->SetDamage(Projectile->GetDamage() * 1.5);
			}

			const auto HalfRad = FMath::DegreesToRadians(Accuracy);
			const FVector ShootDirection = FMath::VRandCone(Direction, HalfRad);
			
			Projectile->SetOwner(GetOwner());
			Projectile->SetShotDirection(ShootDirection);
			Projectile->SetDamage(ProjectileDamage);
			Projectile->FinishSpawning(SpawnTransform);

			GetWorldTimerManager().SetTimer(DelayTimer, this, &ABaseWeapon::ControlFireDelay, FireRate, false);
		}
	}
}
