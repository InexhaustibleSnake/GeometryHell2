// Geometry Hell 2. Made By Alexey Guchmazov

#include "Player/MainPlayerController.h"
#include "Player/Components/StyleComponent.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Sound/SoundWave.h"

AMainPlayerController::AMainPlayerController()
{
	FightAudioComponent = CreateDefaultSubobject<UAudioComponent>("FightAudioComponent");
	AmbientAudioComponent = CreateDefaultSubobject<UAudioComponent>("AmbientAudioComponent");
	StyleComponent = CreateDefaultSubobject<UStyleComponent>("StyleComponent");
}

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();
	FightAudioComponent->SetSound(FightOst);
	AmbientAudioComponent->SetSound(Ambient);
	AmbientAudioComponent->Play(0.0f);
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
	if (EnemiesInFight == 1 && !FightAudioComponent->IsPlaying())
	{
		AmbientAudioComponent->Stop();
		FightAudioComponent->Play(0.0f);
	}
	else if (EnemiesInFight == 0)
	{
		GetWorldTimerManager().SetTimer(FadeOutTimer, this, &AMainPlayerController::FadeMusicOut, 0.1f, false, TimeToChangeFightState);
	}
	else if (FightAudioComponent->bIsFadingOut)
	{
		FightAudioComponent->FadeIn(2.0f, 0.3f);
	}
}

void AMainPlayerController::FadeMusicOut()
{
	if (EnemiesInFight == 0)
	{
		FightAudioComponent->FadeOut(5.0f, 0.05f, EAudioFaderCurve::Linear);
	}
}

void AMainPlayerController::OnPlayerDeath()
{
	UGameplayStatics::PlaySound2D(GetWorld(), GameOverOst);
}

void AMainPlayerController::OnFightEnd()
{
	if (EnemiesInFight == 0)
	{
		IsPlayerInFight = false;
		PlayerInFight.Broadcast(false);

		StyleComponent->ClearStylePoints();

		AmbientAudioComponent->FadeIn(4.0f);
	}
}

void AMainPlayerController::SetFightOst(USoundCue* NewFightOst, bool PlaySound)
{
	if (!NewFightOst) return;

	FightAudioComponent->SetSound(NewFightOst);
	if (PlaySound)
	{
		FightAudioComponent->Play();
	}
}

void AMainPlayerController::SetAmbient(USoundCue* NewAmbient, bool PlaySound)
{
	if (!NewAmbient) return;

	AmbientAudioComponent->SetSound(NewAmbient);
	if (PlaySound)
	{
		AmbientAudioComponent->Play();
	}
}