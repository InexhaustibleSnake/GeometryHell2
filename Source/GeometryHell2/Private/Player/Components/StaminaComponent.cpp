// Geometry Hell 2. Made By Alexey Guchmazov

#include "Player/Components/StaminaComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"

UStaminaComponent::UStaminaComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UStaminaComponent::BeginPlay()
{
	Super::BeginPlay();
	Stamina = MaxStamina;
}

void UStaminaComponent::StartSprinting()
{
	auto PlayerCharacter = Cast<ACharacter>(GetOwner());
	PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
	GetOwner()->GetWorldTimerManager().SetTimer(SprintTimer, this, &UStaminaComponent::StaminaReduce, StaminaReduceRate, true, 0.0f);
}

void UStaminaComponent::StopSprinting()
{
	auto PlayerCharacter = Cast<ACharacter>(GetOwner());
	PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	GetOwner()->GetWorldTimerManager().SetTimer(SprintTimer, this, &UStaminaComponent::StaminaRecovery, StaminaRecoveryRate, true, 0.0f);
}

void UStaminaComponent::StaminaReduce()
{
	if (IsStaminaEmpty() || Stamina < 0.0f)
	{
		GetOwner()->GetWorldTimerManager().SetTimer(SprintTimer, this, &UStaminaComponent::StaminaRecovery, StaminaRecoveryRate, true, 0.0f);
		StopSprinting();
	}

	Stamina = FMath::Clamp(Stamina - StaminaReduceAmount, 0.0f, MaxStamina);
	OnStaminaChange.Broadcast();
}

void UStaminaComponent::StaminaRecovery()
{
	if (IsStaminaFull() || Stamina > MaxStamina)
	{
		GetOwner()->GetWorldTimerManager().ClearTimer(SprintTimer);
	}

	Stamina = FMath::Clamp(Stamina + StaminaRecoveryAmount, 0.0f, MaxStamina);
	OnStaminaChange.Broadcast();
}