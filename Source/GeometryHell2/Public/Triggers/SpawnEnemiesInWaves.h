// Geometry Hell 2. Made By Alexey Guchmazov

#pragma once

#include "CoreMinimal.h"
#include "Triggers/BaseEnemySpawnTrigger.h"
#include "SpawnEnemiesInWaves.generated.h"

UCLASS()
class GEOMETRYHELL2_API ASpawnEnemiesInWaves : public ABaseEnemySpawnTrigger
{
	GENERATED_BODY()
	
protected:
	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void SpawnEnemies() override;

	bool WasAlreadyOverlaped = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Waves")
	int32 WavesAmount = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Waves")
		TMap<AActor*, TSubclassOf<ABaseEnemy>> SpawnData;

private:
	int32 CurrentWave = 0;

};
