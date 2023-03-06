// Geometry Hell 2. Made By Alexey Guchmazov

#include "Player/MainPlayerController.h"
#include "Player/Components/StyleComponent.h"
#include "Player/Components/MasterAudioComponent.h"

AMainPlayerController::AMainPlayerController()
{
	MasterAudioComponent = CreateDefaultSubobject<UMasterAudioComponent>("MasterAudioComponent");
	StyleComponent = CreateDefaultSubobject<UStyleComponent>("StyleComponent");
}

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();

	PlayerInFightStateChange.AddDynamic(MasterAudioComponent, &UMasterAudioComponent::FightStateChange);
}

void AMainPlayerController::UpdateEnemiesInFight(int32 Amount)
{
	EnemiesInFight = FMath::Clamp(EnemiesInFight + Amount, 0, INT32_MAX);

	if (EnemiesInFight > 0)
	{
		if (GetWorldTimerManager().IsTimerActive(FightStateTimer))
		{
			GetWorldTimerManager().ClearTimer(FightStateTimer);
		}
		if (!IsPlayerInFight)
		{
			PlayerInFightStateChange.Broadcast(true);
			IsPlayerInFight = true;
		}
	}
	
	if (EnemiesInFight == 0)
	{
		OnAllEnemiesKilled.Broadcast();
		GetWorldTimerManager().SetTimer(FightStateTimer, this, &AMainPlayerController::OnFightEnd, TimeToChangeFightState, false);
	}
}

void AMainPlayerController::OnFightEnd()
{
	if (EnemiesInFight == 0)
	{
		IsPlayerInFight = false;
		PlayerInFightStateChange.Broadcast(false);

		StyleComponent->ClearStylePoints();

		MasterAudioComponent->StartAmbient();
	}
}
