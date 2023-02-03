// Geometry Hell 2. Made By Alexey Guchmazov

#include "Player/Components/HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool UHealthComponent::TryToAddHealth(float Amount)
{
	if (IsHealthFull()) return false;

	Health = FMath::Clamp(Health + Amount, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast();
	return true;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnTakeAnyDamage);
}

void UHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	SetHealth(Damage);
}

void UHealthComponent::SetHealth(float Amount)
{
	Health = FMath::Clamp(Health - Amount, 0.0f, MaxHealth);

	if (Health == 0)
	{
		OnDeath.Broadcast();
	}
	else
	{
		OnHealthChanged.Broadcast();
	}
}
