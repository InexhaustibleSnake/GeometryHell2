// Geometry Hell 2. Made By Alexey Guchmazov

#include "Enemy/ExplosionEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/TextRenderComponent.h"
#include "Components/SphereComponent.h"
#include "Sound/SoundCue.h"

AExplosionEnemy::AExplosionEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	ExplosionTextTimer = CreateDefaultSubobject<UTextRenderComponent>("ExplosionTextTimer");
	ExplosionTextTimer->SetupAttachment(GetRootComponent());
}

void AExplosionEnemy::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(ExplosionTimer, this, &AExplosionEnemy::Explode, TimeToExplode);
	
}

void AExplosionEnemy::Tick(float DeltaTime)
{
	ExplosionTextTimer->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), GetWorldTimerManager().GetTimerRemaining(ExplosionTimer))));
}

void AExplosionEnemy::Explode()
{
	UGameplayStatics::ApplyRadialDamage(GetWorld(), ExplosionDamage, GetActorLocation(), ExplosionRadius, UDamageType::StaticClass(), {}, this, GetController(), false);
	
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ExplosionParticles, CannonMesh->GetComponentLocation(), GetActorRotation());

	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ExplosionSound, GetActorLocation());

	Destroy();
}
