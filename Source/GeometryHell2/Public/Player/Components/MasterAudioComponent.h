// Geometry Hell 2. Made By Alexey Guchmazov

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MasterAudioComponent.generated.h"

class UAudioComponent;
class USoundCue;
class AMainPlayerController;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GEOMETRYHELL2_API UMasterAudioComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMasterAudioComponent();

	UFUNCTION()
	void FightStateChange(bool InFight);

	void SetFightOst(USoundCue* NewFightOst, bool PlaySound);

	void SetAmbient(USoundCue* NewAmbient, bool PlaySound);

	void StartAmbient();
	void StopAmbient();

	void StartFightOst();
	void StopFightOst();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Audio")
		UAudioComponent* FightAudioComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Audio")
		UAudioComponent* AmbientAudioComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Audio")
		USoundCue* Ambient;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Audio")
		USoundCue* FightOst;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Audio")
		USoundCue* GameOverOst;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Audio")
		float FadeInTime = 4.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Audio")
		float FadeOutDuration = 5.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Audio")
		float FadeOutVolumeLevel = 0.05f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Audio")
		float FadeInVolumeLevel = 0.3f;

private:
	void FadeMusicOut();
	void OnPlayerDeath();

	AMainPlayerController* GetController();

	FTimerHandle FadeOutTimer;
	FTimerHandle FightStateTimer;
};
