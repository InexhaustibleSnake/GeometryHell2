// Geometry Hell 2. Made By Alexey Guchmazov

#pragma once

#include "CoreMinimal.h"
#include "Enemy/BaseEnemy.h"
#include "ExplosionEnemy.generated.h"

class UParticleSystem;

UCLASS()
class GEOMETRYHELL2_API AExplosionEnemy : public ABaseEnemy
{
	GENERATED_BODY()

public:
	AExplosionEnemy();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UTextRenderComponent* ExplosionTextTimer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Explosion")
		float TimeToExplode = 10.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Explosion")
		float ExplosionRadius = 1000.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Explosion")
		float ExplosionDamage = 50.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Explosion")
		float ExplosionImpulseStrength = 500.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Explosion")
		UNiagaraSystem* ExplosionParticles;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Explosion")
		USoundCue* ExplosionSound;

	void Explode();

	FTimerHandle ExplosionTimer;
};
