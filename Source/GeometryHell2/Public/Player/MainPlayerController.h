// Geometry Hell 2. Made By Alexey Guchmazov

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerInFight, bool, InFight);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAllEnemiesKilled);

class UAudioComponent;
class USoundCue;
class UStyleComponent;
class UMasterAudioComponent;

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
	FPlayerInFight PlayerInFightStateChange;

	UPROPERTY(BlueprintAssignable)
	FOnAllEnemiesKilled OnAllEnemiesKilled;

	float const GetTimeToChangeFightState() { return TimeToChangeFightState; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Style")
		UStyleComponent* StyleComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UMasterAudioComponent* MasterAudioComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FightState")
		float TimeToChangeFightState = 10.0f;

private:
	void OnFightEnd();

	int32 EnemiesInFight = 0;
	bool IsPlayerInFight = false;

	FTimerHandle FightStateTimer;
};
