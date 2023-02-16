// Geometry Hell 2. Made By Alexey Guchmazov

#include "Triggers/SpawnEnemiesInWaves.h"
#include "Player/MainPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Player/Emancipator.h"
#include "Enemy/BaseEnemy.h"

void ASpawnEnemiesInWaves::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->GetClass()->IsChildOf(AEmancipator::StaticClass())) return;

	GetWorldTimerManager().SetTimer(CheckNumOfEnemiesTimer, this, &ASpawnEnemiesInWaves::CheckNumOfEnemies, CheckRate, true, 0.0f);
}

void ASpawnEnemiesInWaves::SpawnEnemies()
{
	for (const TPair<AActor*, TSubclassOf<ABaseEnemy>>& Pair : SpawnData)
	{
		FTransform SpawnTransForm = Pair.Key->GetTransform();

		ABaseEnemy* SpawnedEnemy = GetWorld()->SpawnActor<ABaseEnemy>(Pair.Value, SpawnTransForm);
	}

	if (++CurrentWave == WavesAmount) Destroy();
}

void ASpawnEnemiesInWaves::CheckNumOfEnemies()
{
	const auto PlayerController = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (PlayerController->GetEnemiesInFight() == 0)
	{
		SpawnEnemies();
	}
}