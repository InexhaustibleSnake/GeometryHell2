// Geometry Hell 2. Made By Alexey Guchmazov

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StaminaComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStaminaChange);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GEOMETRYHELL2_API UStaminaComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStaminaComponent();

	void StartSprinting();
	void StopSprinting();

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetStaminaPercent() const { return Stamina / MaxStamina; }

	UPROPERTY(BlueprintAssignable)
	FOnStaminaChange OnStaminaChange;

protected:
	virtual void BeginPlay() override;
		
	void StaminaReduce();
	void StaminaRecovery();
	FORCEINLINE bool IsStaminaEmpty() const { return FMath::IsNearlyZero(Stamina); }
	FORCEINLINE bool IsStaminaFull() const { return FMath::IsNearlyEqual(Stamina, MaxStamina); }

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stamina")
		float MaxStamina = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stamina")
		float Stamina;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stamina")
		float StaminaRecoveryRate = 0.01f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stamina")
		float StaminaRecoveryAmount = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stamina")
		float StaminaReduceRate = 0.01f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stamina")
		float StaminaReduceAmount = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stamina")
		float RunSpeed = 700.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stamina")
		float WalkSpeed = 400.0f;

	FTimerHandle SprintTimer;
};
