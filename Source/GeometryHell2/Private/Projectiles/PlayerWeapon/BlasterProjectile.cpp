// Geometry Hell 2. Made By Alexey Guchmazov

#include "Projectiles/PlayerWeapon/BlasterProjectile.h"
#include "Player/Emancipator.h"
#include "Player/Components/StyleComponent.h"

void ABlasterProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!OtherActor)
	{
		Destroy();
		return;
	}
	
	const auto Player = Cast<APawn>(GetOwner());

	if (OtherActor == Player) return;

	OtherActor->TakeDamage(BaseDamage, FDamageEvent{}, GetController(), this);

	AddStylePoints();

	Destroy();
}

void ABlasterProjectile::AddStylePoints()
{
	const auto Player = Cast<APawn>(GetOwner());
	auto PlayerController = Cast<APlayerController>(Player->GetController());

	auto StyleComponent = PlayerController->FindComponentByClass<UStyleComponent>();
	StyleComponent->AddStylePoints(StylePointsForHit);
}

AController* ABlasterProjectile::GetController() const
{
	const auto Pawn = Cast<APawn>(GetOwner());
	return Pawn ? Pawn->GetController() : nullptr;
}
