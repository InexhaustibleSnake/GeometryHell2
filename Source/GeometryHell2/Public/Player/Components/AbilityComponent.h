// Geometry Hell 2. Made By Alexey Guchmazov

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AbilityComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbilityStaminaChange, float, NewAbilityStamina);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GEOMETRYHELL2_API UAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAbilityComponent();
	void TimeManager(bool StopTime);
	void RestoreTime();

	UPROPERTY(BlueprintAssignable)
	FOnAbilityStaminaChange OnAbilityStaminaChange;

protected:
	virtual void BeginPlay() override;
	void EnableSlowTime();
	void EnableTimeStop();
	void DecreaseAbilityStamina();
	void RestoreAbilityStamina();
	FORCEINLINE float GetAbilityStamina() const { return AbilityStamina; }
	FORCEINLINE float AbilityStaminaIsFull() const { return FMath::IsNearlyEqual(AbilityStamina, MaxAbilityStamina); }

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stamina")
		float MaxAbilityStamina = 10.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stamina")
		float AbilityStamina;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stamina")
		float AbilityStaminaRestore = 0.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stamina")
		float AbilityStaminaRestoreRate = 0.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SlowTime")
		float SlowTimeStrength = 0.7f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SlowTime")
		float AbilityStaminaReduceSlowTimeRate = 0.7f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SlowTime")
		float AbilityStaminaReduceSlowTimeAmount = 1.7f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "StopTime")
		float StopTimeStrength = 0.01f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "StopTime")
		float PlayerSpeedInStopTime = 500.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "StopTime")
		float AbilityStaminaReduceStopTimeRate = 0.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "StopTime")
		float AbilityStaminaReduceStopTimeAmount = 1.5f;

private:

	bool TimeStopActive = false;
	FTimerHandle TimeManagerTimer;
	FTimerHandle StaminaRestoreTimer;
};
