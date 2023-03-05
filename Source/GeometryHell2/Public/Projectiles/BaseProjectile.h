// Geometry Hell 2. Made By Alexey Guchmazov

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseProjectile.generated.h"

class UProjectileMovementComponent;
class UBoxComponent;

UCLASS()
class GEOMETRYHELL2_API ABaseProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseProjectile();

	void SetShotDirection(const FVector& Direction) { ShotDirection = Direction; }

	void SetDamage(float Damage) { BaseDamage = Damage; }

	float GetDamage() const { return BaseDamage; }
   
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UBoxComponent* BoxCollision;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Properities")
		float LifeSpan = 5.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Properities")
		float BaseDamage = 10.0f;

private:
	FVector ShotDirection;

	UFUNCTION()
		virtual void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
