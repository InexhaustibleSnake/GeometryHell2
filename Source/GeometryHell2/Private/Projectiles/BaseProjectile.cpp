// Geometry Hell 2. Made By Alexey Guchmazov

#include "Projectiles/BaseProjectile.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

ABaseProjectile::ABaseProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	SetRootComponent(BoxCollision);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
}

void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(LifeSpan);
	ProjectileMovementComponent->Velocity = ProjectileMovementComponent->InitialSpeed * ShotDirection;

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ABaseProjectile::OnCollision);
}

void ABaseProjectile::OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	if (OtherActor == GetOwner()) return;
	OtherActor->TakeDamage(BaseDamage, FDamageEvent{}, nullptr, this);
	Destroy();
}
