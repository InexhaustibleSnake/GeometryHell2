// Geometry Hell 2. Made By Alexey Guchmazov

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

class USkeletalMeshComponent;
class ABaseProjectile;
class UCameraShakeBase;
class USoundCue;

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
	void GetTraceData(FVector& TraceStart, FVector& TraceEnd);
	void MakeTrace(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);
	void PlayCameraShake();
	const AController* GetPlayerController();
	FVector GetMuzzleWorldLocation();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		float ProjectileDamage = 5.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		float FireRate = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		float Accuracy = 3.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		TSubclassOf<ABaseProjectile> ProjectileToSpawn;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TSubclassOf<UCameraShakeBase> CameraShake;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Audio")
		USoundCue* ShootAudio;

	FTimerHandle FireTimer;
	FTimerHandle DelayTimer;

	float TraceMaxDistance = 16000.0f;
	bool CanFire = true;
};
