// Geometry Hell 2. Made By Alexey Guchmazov

#include "Triggers/EnemyVariousSpawnTrigger.h"
#include "Player/MainPlayerController.h"
#include "Player/Emancipator.h"
#include "Enemy/BaseEnemy.h"

void AEnemyVariousSpawnTrigger::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->GetClass()->IsChildOf(AEmancipator::StaticClass())) return;

	if (!WasAlreadyOverlaped)
	{
		const auto Player = Cast<APawn>(OtherActor);
		if (!Player) return;

		const auto Controller = Cast<AMainPlayerController>(Player->GetController());
		Controller->OnAllEnemiesKilled.AddDynamic(this, &AEnemyVariousSpawnTrigger::SpawnEnemies);

		SpawnEnemies();

		WasAlreadyOverlaped = true;
	}
}

void AEnemyVariousSpawnTrigger::SpawnEnemies()
{
	for (int i = CurrentWave; SpawnData.Num(); ++i)
	{
		for (const TPair<AActor*, TSubclassOf<ABaseEnemy>>& Pair : SpawnData[i].EnemySpawnData)
		{
			if (!Pair.Key && !Pair.Value) return;
			FTransform SpawnTransForm = Pair.Key->GetTransform();	
		
			ABaseEnemy* SpawnedEnemy = GetWorld()->SpawnActor<ABaseEnemy>(Pair.Value, SpawnTransForm);
		}
		break;
	}

	if (++CurrentWave == SpawnData.Num()) Destroy();
}
