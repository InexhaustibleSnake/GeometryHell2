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

	if (OtherActor->GetClass()->IsChildOf(AEmancipator::StaticClass())) return;
	OtherActor->TakeDamage(BaseDamage, FDamageEvent{}, Player->GetController(), this);

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
