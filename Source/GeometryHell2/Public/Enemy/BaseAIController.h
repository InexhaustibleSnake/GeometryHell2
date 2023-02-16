// Geometry Hell 2. Made By Alexey Guchmazov

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseAIController.generated.h"

class UAIPerceptionComponent;
class UBehaviorTree;
class AEmancipator;

UCLASS()
class GEOMETRYHELL2_API ABaseAIController : public AAIController
{
	GENERATED_BODY()

public:
	ABaseAIController();

	UFUNCTION()
		void OnDestroy();

	bool SpotPlayer = false;

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void UpdateEnemiesInFight(int32 Amount);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UAIPerceptionComponent* AIPerceptionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		FName FocusOnKeyName = "PlayerActor";

private:
	UFUNCTION()
	void ActorsUpdated(TArray<AActor*> const& UpdatedActors);

	AEmancipator* Player;

};
