// Geometry Hell 2. Made By Alexey Guchmazov

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerInFight, bool, InFight);

class UAudioComponent;
class USoundCue;
class UStyleComponent;

UCLASS()
class GEOMETRYHELL2_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	AMainPlayerController();

	void UpdateEnemiesInFight(int32 Amount);

	UFUNCTION(BlueprintCallable)
	int32 GetEnemiesInFight() const { return EnemiesInFight; }

	UPROPERTY(BlueprintAssignable)
	FPlayerInFight PlayerInFight;

	void SetFightOst(USoundCue* NewFightOst, bool PlaySound);
	void SetAmbient(USoundCue* NewAmbient, bool PlaySound);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Style")
		UStyleComponent* StyleComponent;

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FightState")
		float TimeToChangeFightState = 20.0f;

private:
	void ChangePlayingOst();
	void FadeMusicOut();
	void OnPlayerDeath();
	void OnFightEnd();

	int32 EnemiesInFight = 0;
	bool IsPlayerInFight = false;

	FTimerHandle FadeOutTimer;
	FTimerHandle FightStateTimer;
};
