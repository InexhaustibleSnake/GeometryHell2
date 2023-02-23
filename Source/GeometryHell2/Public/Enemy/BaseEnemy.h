// Geometry Hell 2. Made By Alexey Guchmazov

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseEnemy.generated.h"

class UTextRenderComponent;
class UParticleSystem;
class USoundCue;
class UNiagaraSystem;
class UBehaviorTree;
class ABaseProjectile;

DECLARE_MULTICAST_DELEGATE(FOnDeath);

UCLASS()
class GEOMETRYHELL2_API ABaseEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseEnemy();
	void ShootStart();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
		UBehaviorTree* BehaviorTreeAsset;

	FOnDeath OnDeath;

protected:
	virtual void BeginPlay() override;
	UFUNCTION()
	virtual void OnTakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
	virtual void Destroyed() override;

	void ShootProjectile();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* CannonMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* MainMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UTextRenderComponent* HealthRenderComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
		float MaxHealth = 100;
		float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
		float FireRate = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Cores")
		float CoresForKill = 10.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Cores")
		float StylePointForKill = 0.25f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile")
		TSubclassOf<ABaseProjectile> MainProjectile;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Audio")
		USoundCue* ShootSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Audio")
		USoundCue* DamagedSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Audio")
		USoundCue* DeathSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Particles")
		UNiagaraSystem* OnDamagedParticles;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Particles")
		UNiagaraSystem* OnDestroyedParticles;

	FTimerHandle ShootTimer;
};
