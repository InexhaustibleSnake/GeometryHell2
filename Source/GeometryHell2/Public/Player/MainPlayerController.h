// Geometry Hell 2. Made By Alexey Guchmazov

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

class UAudioComponent;
class USoundCue;

UCLASS()
class GEOMETRYHELL2_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	AMainPlayerController();

	void UpdateEnemiesInFight(int32 Amount);

	UFUNCTION(BlueprintCallable)
	int32 GetEnemiesInFight() const { return EnemiesInFight; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Audio")
		UAudioComponent* AudioComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Audio")
		USoundCue* FightOst;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
		USoundCue* GameOverOst;

private:
	void ChangePlayingOst();
	void FadeMusicOut();
	void OnPlayerDeath();

	int32 EnemiesInFight = 0;

	FTimerHandle FadeOutTimer;
};
