// Geometry Hell 2. Made By Alexey Guchmazov

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseEnemySpawnTrigger.generated.h"

class ABaseEnemy;
class UBoxComponent;

UCLASS()
class GEOMETRYHELL2_API ABaseEnemySpawnTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseEnemySpawnTrigger();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void SpawnEnemies();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UBoxComponent* BoxTrigger;


};
