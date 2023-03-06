// Geometry Hell 2. Made By Alexey Guchmazov

#pragma once

#include "CoreMinimal.h"
#include "Triggers/BaseEnemySpawnTrigger.h"
#include "EnemyVariousSpawnTrigger.generated.h"

USTRUCT(BlueprintType)
struct FSpawnDatas
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Waves")
	TMap<AActor*, TSubclassOf<ABaseEnemy>> EnemySpawnData;
};

UCLASS()
class GEOMETRYHELL2_API AEnemyVariousSpawnTrigger : public ABaseEnemySpawnTrigger
{
	GENERATED_BODY()

protected:
	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void SpawnEnemies() override;

	bool WasAlreadyOverlaped = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Waves")
		TArray<FSpawnDatas> SpawnData;

private:
	int32 CurrentWave = 0;

};
