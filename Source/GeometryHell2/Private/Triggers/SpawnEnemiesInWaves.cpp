// Geometry Hell 2. Made By Alexey Guchmazov

#include "Triggers/SpawnEnemiesInWaves.h"
#include "Player/MainPlayerController.h"
#include "Player/Emancipator.h"
#include "Enemy/BaseEnemy.h"

void ASpawnEnemiesInWaves::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->GetClass()->IsChildOf(AEmancipator::StaticClass())) return;

	if (!WasAlreadyOverlaped)
	{
		const auto Player = Cast<APawn>(OtherActor);
		if (!Player) return;

		const auto Controller = Cast<AMainPlayerController>(Player->GetController());
		Controller->OnAllEnemiesKilled.AddDynamic(this, &ASpawnEnemiesInWaves::SpawnEnemies);
		
		SpawnEnemies();

		WasAlreadyOverlaped = true;
	}
}

void ASpawnEnemiesInWaves::SpawnEnemies()
{
	for (const TPair<AActor*, TSubclassOf<ABaseEnemy>>& Pair : SpawnData)
	{
		if (!Pair.Key && !Pair.Value) return;
		FTransform SpawnTransForm = Pair.Key->GetTransform();

		ABaseEnemy* SpawnedEnemy = GetWorld()->SpawnActor<ABaseEnemy>(Pair.Value, SpawnTransForm);
	}

	if (++CurrentWave == WavesAmount) Destroy();
}
