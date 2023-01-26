// Geometry Hell 2. Made By Alexey Guchmazov

#include "Player/MainPlayerController.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

AMainPlayerController::AMainPlayerController()
{
	AudioComponent = CreateDefaultSubobject<UAudioComponent>("AudioComponent");
}

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();

}

void AMainPlayerController::UpdateEnemiesInFight(int32 Amount)
{
	EnemiesInFight += Amount;
	ChangePlayingOst();
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