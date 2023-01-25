// Geometry Hell 2. Made By Alexey Guchmazov

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseEnemy.generated.h"

class UTextRenderComponent;
class UParticleSystem;
class USoundCue;
class UNiagaraSystem;

UCLASS()
class GEOMETRYHELL2_API ABaseEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseEnemy();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	UFUNCTION()
	virtual void OnTakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
	virtual void Destroyed() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* CannonMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* MainMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UTextRenderComponent* HealthRenderComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
		float MaxHealth = 100;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
		float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Audio")
		USoundCue* DamagedSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Audio")
		USoundCue* DeathSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Particles")
		UNiagaraSystem* OnDamagedParticles;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Particles")
		UParticleSystem* OnDestroyedParticles;
};
