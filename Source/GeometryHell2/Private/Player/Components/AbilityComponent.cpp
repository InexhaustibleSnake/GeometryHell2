// Geometry Hell 2. Made By Alexey Guchmazov

#include "Player/Components/AbilityComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/Emancipator.h"
#include "GameFramework/Character.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/MovementComponent.h"

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

void UAbilityComponent::Dash()
{
	if (AbilityStamina <= 5.0f) return;

	FVector TraceStart, TraceEnd;
	FRotator TraceRotation;
	auto Player = Cast<ACharacter>(GetOwner());
	
	Player->GetController()->GetPlayerViewPoint(TraceStart, TraceRotation);
	TraceEnd = TraceStart + Player->GetActorForwardVector() * DashStrength;

	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);
	
	Player->SetActorLocation(HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd);

	AbilityStamina = FMath::Clamp(AbilityStamina - DashStaminaUsage, 0.0f, MaxAbilityStamina);

	Player->GetCharacterMovement()->StopMovementImmediately();

	GetWorld()->GetTimerManager().SetTimer(StaminaRestoreTimer, this, &UAbilityComponent::RestoreAbilityStamina, AbilityStaminaRestoreRate, true, 0.0f);
}
