// Geometry Hell 2. Made By Alexey Guchmazov

#include "Player/Components/MasterAudioComponent.h"
#include "Player/Components/HealthComponent.h"
#include "Player/MainPlayerController.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

UMasterAudioComponent::UMasterAudioComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
 
	FightAudioComponent = CreateDefaultSubobject<UAudioComponent>("FightAudioComponent");
	AmbientAudioComponent = CreateDefaultSubobject<UAudioComponent>("AmbientAudioComponent");
}

void UMasterAudioComponent::BeginPlay()
{
	Super::BeginPlay();

	FightAudioComponent->SetSound(FightOst);
	AmbientAudioComponent->SetSound(Ambient);

	auto Player = GetOwner();
	if (!Player) return;

	auto PlayerHealthComponent = Player->FindComponentByClass<UHealthComponent>();
	if (!PlayerHealthComponent) return;

	PlayerHealthComponent->OnDeath.AddDynamic(this, &UMasterAudioComponent::OnPlayerDeath);
}

void UMasterAudioComponent::FightStateChange(bool InFight)
{
	if (InFight)
	{
		if (!FightAudioComponent->IsPlaying())
		{
			StopAmbient();
			StartFightOst();
		}
		else
		{
			FightAudioComponent->FadeIn(FadeInTime, FadeInVolumeLevel);
		}
	}

	if (!InFight)
	{
		GetWorld()->GetTimerManager().SetTimer(FadeOutTimer, this, &UMasterAudioComponent::FadeMusicOut, GetController()->GetTimeToChangeFightState(), false);
	}
}

void UMasterAudioComponent::SetFightOst(USoundCue* NewFightOst, bool PlaySound)
{
	if (!NewFightOst) return;

	FightAudioComponent->SetSound(NewFightOst);
	if (PlaySound)
	{
		FightAudioComponent->Play();
	}
}

void UMasterAudioComponent::SetAmbient(USoundCue* NewAmbient, bool PlaySound)
{
	if (!NewAmbient) return;

	AmbientAudioComponent->SetSound(NewAmbient);
	if (PlaySound)
	{
		AmbientAudioComponent->Play();
	}
}

void UMasterAudioComponent::FadeMusicOut()
{
	FightAudioComponent->FadeOut(FadeOutDuration, FadeOutVolumeLevel);
}

void UMasterAudioComponent::OnPlayerDeath()
{
	UGameplayStatics::PlaySound2D(GetWorld(), GameOverOst);
}

void UMasterAudioComponent::StartAmbient()
{
	AmbientAudioComponent->FadeIn(FadeInTime);
}

void UMasterAudioComponent::StopAmbient()
{
	AmbientAudioComponent->Stop();
}

void UMasterAudioComponent::StartFightOst()
{
	FightAudioComponent->Play(0.0f);
}

void UMasterAudioComponent::StopFightOst()
{
	FightAudioComponent->Stop();
}

AMainPlayerController* UMasterAudioComponent::GetController()
{
	const auto Controller = Cast<AMainPlayerController>(GetOwner());
	if (!Controller) return nullptr;

	return Controller;
}