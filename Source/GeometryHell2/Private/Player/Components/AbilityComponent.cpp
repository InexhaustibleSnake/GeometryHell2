// Geometry Hell 2. Made By Alexey Guchmazov

#include "Player/Components/AbilityComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/Emancipator.h"
#include "GameFramework/Character.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/MovementComponent.h"
#include "UObject/Object.h"
#include "Engine/EngineTypes.h"
#include "Sound/SoundWave.h"

UAbilityComponent::UAbilityComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAbilityComponent::BeginPlay()
{
	Super::BeginPlay();
	AbilityStamina = MaxAbilityStamina;
	const auto Player = Cast<ACharacter>(GetOwner());
	if (!Player) return;
	const auto MovementComponent = Player->FindComponentByClass<UCharacterMovementComponent>();
	PlayerGravityScale = MovementComponent->GravityScale;
}

void UAbilityComponent::TimeManager(bool StopTime)
{
	if (IsTimerActive(TimeManagerTimer)) return;
	StopTime ? EnableTimeStop() : EnableSlowTime();
}

void UAbilityComponent::EnableSlowTime()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), SlowTimeStrength);

	SetTimerInComponent(TimeManagerTimer, this, &UAbilityComponent::DecreaseAbilityStamina, AbilityStaminaReduceSlowTimeRate, true, 0.0f);

	if (IsTimerActive(StaminaRestoreTimer))
	{
		ClearTimer(StaminaRestoreTimer);
	}
}

void UAbilityComponent::EnableTimeStop()
{
	if (GetOwner()->GetVelocity().IsZero())
	{
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), StopTimeStrength);

		GetOwner()->CustomTimeDilation = PlayerSpeedInStopTime;

		UGameplayStatics::PlaySound2D(GetWorld(), TimeStopSound);

		TimeStopActive = true;

		SetTimerInComponent(TimeManagerTimer, this, &UAbilityComponent::DecreaseAbilityStamina, AbilityStaminaReduceStopTimeRate, true, 0.0f);

		if (IsTimerActive(StaminaRestoreTimer))
		{
			ClearTimer(StaminaRestoreTimer);
		}
	}
}

void UAbilityComponent::DecreaseAbilityStamina()
{
	if (GetAbilityStamina() <= 0.0f)
	{
		RestoreTime();
	}

	AbilityStamina -= FMath::Clamp(TimeStopActive ? AbilityStaminaReduceStopTimeAmount : AbilityStaminaReduceSlowTimeAmount, 0.0f, MaxAbilityStamina);
	OnAbilityStaminaChange.Broadcast();
}

void UAbilityComponent::RestoreTime()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
	ClearTimer(TimeManagerTimer);
	if (TimeStopActive)
	{
		GetOwner()->CustomTimeDilation = 1.0f;

		UGameplayStatics::PlaySound2D(GetWorld(), TimeResumeSound);

		TimeStopActive = false;
	}

	SetTimerInComponent(StaminaRestoreTimer, this, &UAbilityComponent::RestoreAbilityStamina, AbilityStaminaRestoreRate, true, 0.0f);
}

void UAbilityComponent::RestoreAbilityStamina()
{
	if (AbilityStaminaIsFull()) 
	{ 
		ClearTimer(StaminaRestoreTimer); 
	}

	AbilityStamina = FMath::Clamp(AbilityStamina + AbilityStaminaRestore, 0.0f, MaxAbilityStamina);
	OnAbilityStaminaChange.Broadcast();
}

void UAbilityComponent::Dash()
{
	if (AbilityStamina <= DashStaminaUsage) return;

	const auto Player = Cast<ACharacter>(GetOwner());
	if (!Player) return;
	auto MovementComponent = Player->FindComponentByClass<UCharacterMovementComponent>();
	
	if (MovementComponent->IsFalling())
	{
		MovementComponent->AddImpulse(Player->GetActorForwardVector() * InAirDashStrength);
        
		SetTimerInComponent(DashTimer, this, &UAbilityComponent::RestoreGravityAfterDash, 0.1f, false, 0.1f);
	}
	else
	{
		MovementComponent->AddImpulse(Player->GetActorForwardVector() * OnFloorDashStrength);
	}

	SetTimerInComponent(StaminaRestoreTimer, this, &UAbilityComponent::RestoreAbilityStamina, AbilityStaminaRestoreRate, true, 0.0f);
	AbilityStamina = FMath::Clamp(AbilityStamina - DashStaminaUsage, 0.0f, MaxAbilityStamina);
}

void UAbilityComponent::RestoreGravityAfterDash()
{
	const auto Player = Cast<ACharacter>(GetOwner());
	if (!Player) return;

	auto MovementComponent = Player->FindComponentByClass<UCharacterMovementComponent>();
	MovementComponent->StopMovementImmediately();

	MovementComponent->GravityScale = PlayerGravityScale;
}

bool UAbilityComponent::TryToAddAbilityStamina(float Amount)
{
	if (AbilityStaminaIsFull()) return false;

	AbilityStamina = FMath::Clamp(AbilityStamina + Amount, 0.0f, MaxAbilityStamina);
	return true;
}

bool UAbilityComponent::IsTimerActive(FTimerHandle& Timer)
{
	return GetWorld()->GetTimerManager().IsTimerActive(Timer);
}

void UAbilityComponent::ClearTimer(FTimerHandle& Timer)
{
	GetWorld()->GetTimerManager().ClearTimer(Timer);
}
