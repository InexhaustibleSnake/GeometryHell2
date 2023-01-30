// Geometry Hell 2. Made By Alexey Guchmazov

#include "Player/Components/AbilityComponent.h"
#include "Kismet/GameplayStatics.h"

UAbilityComponent::UAbilityComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAbilityComponent::BeginPlay()
{
	Super::BeginPlay();
	AbilityStamina = MaxAbilityStamina;
}

void UAbilityComponent::TimeManager(bool StopTime)
{
	if (!GetWorld() && GetWorld()->GetTimerManager().IsTimerActive(TimeManagerTimer)) return;
	StopTime ? EnableTimeStop() : EnableSlowTime();
}

void UAbilityComponent::EnableSlowTime()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(TimeManagerTimer)) return;

	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), SlowTimeStrength);

	GetWorld()->GetTimerManager().SetTimer(TimeManagerTimer, this, &UAbilityComponent::DecreaseAbilityStamina, AbilityStaminaReduceSlowTimeRate, true, 0.0f);

	if (GetWorld()->GetTimerManager().IsTimerActive(StaminaRestoreTimer))
	{
		GetWorld()->GetTimerManager().ClearTimer(StaminaRestoreTimer);
	}
}

void UAbilityComponent::EnableTimeStop()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(TimeManagerTimer)) return;

	if (GetOwner()->GetVelocity().IsZero()) {
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), StopTimeStrength);

		GetOwner()->CustomTimeDilation = PlayerSpeedInStopTime;

		TimeStopActive = true;

		GetWorld()->GetTimerManager().SetTimer(TimeManagerTimer, this, &UAbilityComponent::DecreaseAbilityStamina, AbilityStaminaReduceStopTimeRate, true, 0.0f);

		if (GetWorld()->GetTimerManager().IsTimerActive(StaminaRestoreTimer))
		{
			GetWorld()->GetTimerManager().ClearTimer(StaminaRestoreTimer);
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
	GetWorld()->GetTimerManager().ClearTimer(TimeManagerTimer);
	if (TimeStopActive)
	{
		GetOwner()->CustomTimeDilation = 1.0f;
		TimeStopActive = false;
	}

	GetWorld()->GetTimerManager().SetTimer(StaminaRestoreTimer, this, &UAbilityComponent::RestoreAbilityStamina, AbilityStaminaRestoreRate, true, 0.0f);
}

void UAbilityComponent::RestoreAbilityStamina()
{
	if (AbilityStaminaIsFull()) { GetWorld()->GetTimerManager().ClearTimer(StaminaRestoreTimer); }

	AbilityStamina = FMath::Clamp(AbilityStamina + AbilityStaminaRestore, 0.0f, MaxAbilityStamina);
	OnAbilityStaminaChange.Broadcast();
}