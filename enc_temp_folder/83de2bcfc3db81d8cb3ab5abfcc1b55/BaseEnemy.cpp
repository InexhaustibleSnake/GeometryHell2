// Geometry Hell 2. Made By Alexey Guchmazov

#include "Enemy/BaseEnemy.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "NiagaraFunctionLibrary.h"
#include "Enemy/BaseAIController.h"
#include "Projectiles/BaseProjectile.h"

ABaseEnemy::ABaseEnemy()
{
	PrimaryActorTick.bCanEverTick = false;

	MainMesh = CreateDefaultSubobject<UStaticMeshComponent>("MainMesh");
	MainMesh->SetupAttachment(GetRootComponent());

	CannonMesh = CreateDefaultSubobject<UStaticMeshComponent>("CannonMesh");
	CannonMesh->SetupAttachment(GetRootComponent());

	HealthRenderComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthRender");
	HealthRenderComponent->SetupAttachment(GetRootComponent());

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	HealthRenderComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), MaxHealth)));
	HealthRenderComponent->SetTextRenderColor(FColor::Red);

	OnTakeAnyDamage.AddDynamic(this, &ABaseEnemy::OnTakeDamage);
}

void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseEnemy::OnTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
	if (Health <= 0)
	{
		Destroyed();
		return;
	}

	HealthRenderComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), DamagedSound, GetActorLocation());
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), OnDamagedParticles, CannonMesh->GetComponentLocation(), GetActorRotation());
}

void ABaseEnemy::Destroyed()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), OnDestroyedParticles, GetActorTransform(), true, EPSCPoolMethod::AutoRelease);
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), DeathSound, GetActorLocation());
	OnDeath.Broadcast();
	//GetController()->Destroy();
	Destroy();
}

void ABaseEnemy::ShootStart()
{
	GetWorldTimerManager().SetTimer(ShootTimer, this, &ABaseEnemy::ShootProjectile, FireRate, true);
}

void ABaseEnemy::ShootProjectile()
{
	const FTransform SpawnTransform(FRotator::ZeroRotator, CannonMesh->GetComponentLocation());

	ABaseProjectile* Projectile = GetWorld()->SpawnActorDeferred<ABaseProjectile>(MainProjectile, SpawnTransform);

	if (Projectile)
	{
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ShootSound, GetActorLocation());
		Projectile->SetShotDirection(CannonMesh->GetForwardVector());
		Projectile->SetOwner(GetOwner());
		Projectile->FinishSpawning(SpawnTransform);
	}
}