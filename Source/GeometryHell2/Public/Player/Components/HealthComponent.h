// Geometry Hell 2. Made By Alexey Guchmazov

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHealthChanged);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GEOMETRYHELL2_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();
	float IsHealthFull() const { return Health == MaxHealth; }
	bool TryToAddHealth(float Amount);

	UPROPERTY(BlueprintAssignable)
	    FOnHealthChanged OnHealthChanged;
	
	UPROPERTY(BlueprintAssignable)
		FOnDeath OnDeath;

	UFUNCTION(BlueprintCallable)
		FORCEINLINE float GetHealthPercent() const { return Health / MaxHealth; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
		float MaxHealth = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float Health;
		
	FORCEINLINE bool IsKilled() const { return FMath::IsNearlyZero(Health); }

	UFUNCTION()
		void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	void SetHealth(float Amount);
};
