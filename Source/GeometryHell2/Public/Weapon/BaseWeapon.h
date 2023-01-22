// Geometry Hell 2. Made By Alexey Guchmazov

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

class USkeletalMeshComponent;

USTRUCT(BlueprintType)
struct FWeaponParameters
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		float ProjectileDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		float FireRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		float Accuracy;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		int32 NumOfProjectiles;

};

class ABaseProjectile;

UCLASS()
class GEOMETRYHELL2_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseWeapon();

	virtual void StartFire();
	virtual void StopFire();

	void ControlFireDelay() { CanFire = true; }

protected:
	virtual void BeginPlay() override;
	virtual void MakeShot();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FWeaponParameters WeaponParams{ 1, 0.2f, 2.0f };

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TSubclassOf<ABaseProjectile> ProjectileToSpawn;

	FTimerHandle FireTimer;
	FTimerHandle DelayTimer;

	void GetTraceData(FVector& TraceStart, FVector& TraceEnd);
	void MakeTrace(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);
	const AController* GetPlayerController();
	FVector GetMuzzleWorldLocation();

	float TraceMaxDistance = 16000.0f;
	bool CanFire = true;
};
