// Geometry Hell 2. Made By Alexey Guchmazov

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChangeOst.generated.h"

class UBoxComponent;
class USoundCue;

UCLASS()
class GEOMETRYHELL2_API AChangeOst : public AActor
{
	GENERATED_BODY()
	
public:	
	AChangeOst();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio Ambient")
		bool OverrideAmbient = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio Ambient", meta = (EditCondition = "OverrideAmbient"))
		bool PlayNewAmbient = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio Ambient", meta = (EditCondition = "OverrideAmbient"))
		USoundCue* Ambient;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio FightOst")
		bool OverrideBattleOst = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio FightOst", meta = (EditCondition = "OverrideBattleOst"))
		bool PlayNewFightOst = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio FightOst", meta = (EditCondition = "OverrideBattleOst"))
		USoundCue* FightOst;

	UFUNCTION()
		virtual void OnPlayerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
