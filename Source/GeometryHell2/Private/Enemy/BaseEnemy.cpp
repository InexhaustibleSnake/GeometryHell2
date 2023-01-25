// Geometry Hell 2. Made By Alexey Guchmazov

#include "Enemy/BaseEnemy.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "NiagaraFunctionLibrary.h"

ABaseEnemy::ABaseEnemy()
{
	PrimaryActorTick.bCanEverTick = false;

	MainMesh = CreateDefaultSubobject<UStaticMeshComponent>("MainMesh");
	MainMesh->SetupAttachment(GetRootComponent());

	CannonMesh = CreateDefaultSubobject<UStaticMeshComponent>("CannonMesh");
	CannonMesh->SetupAttachment(GetRootComponent());

	HealthRenderComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthRender");
	HealthRenderComponent->SetupAttachment(GetRootComponent());
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
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), OnDamagedParticles, GetActorLocation(), GetActorRotation());
}

void ABaseEnemy::Destroyed()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), OnDestroyedParticles, GetActorTransform(), true, EPSCPoolMethod::AutoRelease);
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), DeathSound, GetActorLocation());
	Destroy();
}
