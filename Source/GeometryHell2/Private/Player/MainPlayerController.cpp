// Geometry Hell 2. Made By Alexey Guchmazov

#include "Player/MainPlayerController.h"
#include "Player/Components/StyleComponent.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

AMainPlayerController::AMainPlayerController()
{
	AudioComponent = CreateDefaultSubobject<UAudioComponent>("AudioComponent");
	StyleComponent = CreateDefaultSubobject<UStyleComponent>("StyleComponent");
}

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();
	AudioComponent->SetSound(FightOst);
}

void AMainPlayerController::UpdateEnemiesInFight(int32 Amount)
{
	EnemiesInFight = FMath::Clamp(EnemiesInFight + Amount, 0, INT32_MAX);

	ChangePlayingOst();

	if (EnemiesInFight > 0)
	{
		if (GetWorldTimerManager().IsTimerActive(FightStateTimer))
		{
			GetWorldTimerManager().ClearTimer(FightStateTimer);
		}
		if (!IsPlayerInFight)
		{
			PlayerInFight.Broadcast(true);
			IsPlayerInFight = true;
		}
	}
	
	if (EnemiesInFight == 0)
	{
		GetWorldTimerManager().SetTimer(FightStateTimer, this, &AMainPlayerController::OnFightEnd, 0.1f, false, TimeToChangeFightState);
	}
}

void AMainPlayerController::ChangePlayingOst()
{
	if (EnemiesInFight == 1 && !AudioComponent->IsPlaying())
	{
		AudioComponent->Play(0.0f);
	}
	else if (EnemiesInFight == 0)
	{
		GetWorldTimerManager().SetTimer(FadeOutTimer, this, &AMainPlayerController::FadeMusicOut, 4.0f, false, 4.0f);
	}
	else if (AudioComponent->bIsFadingOut)
	{
		AudioComponent->FadeIn(2.0f, 0.3f);
	}
}

void AMainPlayerController::FadeMusicOut()
{
	if (EnemiesInFight == 0)
	{
		AudioComponent->FadeOut(4.0f, 0.05f, EAudioFaderCurve::Linear);
	}
}

void AMainPlayerController::OnPlayerDeath()
{
	UGameplayStatics::PlaySound2D(GetWorld(), GameOverOst);
}

void AMainPlayerController::OnFightEnd()
{
	if (EnemiesInFight > 0) return;
	IsPlayerInFight = false;
	PlayerInFight.Broadcast(false);
	StyleComponent->ClearStylePoints();
}
