// Geometry Hell 2. Made By Alexey Guchmazov

#include "Triggers/BaseEnemySpawnTrigger.h"
#include "Enemy/BaseEnemy.h"
#include "Components/BoxComponent.h"

ABaseEnemySpawnTrigger::ABaseEnemySpawnTrigger()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxTrigger = CreateDefaultSubobject<UBoxComponent>("BoxTrigger");
	BoxTrigger->SetupAttachment(GetRootComponent());
}

void ABaseEnemySpawnTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	BoxTrigger->OnComponentBeginOverlap.AddDynamic(this, &ABaseEnemySpawnTrigger::BeginOverlap);
}

//void ABaseEnemySpawnTrigger::NotifyActorBeginOverlap(AActor* OtherActor)
//{
//	
//}

void ABaseEnemySpawnTrigger::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	for (const TPair<AActor*, TSubclassOf<ABaseEnemy>>& Pair : SpawnData)
	{
		FTransform SpawnTransForm = Pair.Key->GetTransform();

		ABaseEnemy* SpawnedEnemy = GetWorld()->SpawnActor<ABaseEnemy>(Pair.Value, SpawnTransForm);
	}
	Destroy();
}