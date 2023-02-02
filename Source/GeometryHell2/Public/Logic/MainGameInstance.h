// Geometry Hell 2. Made By Alexey Guchmazov

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MainGameInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCoresChanged);

UCLASS()
class GEOMETRYHELL2_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	void AddCores(float Amount);
	float GetCores() const { return NumOfCores; }

	FOnCoresChanged OnCoresChanged;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Health")
		float PlayerMaxHealth = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Ability")
		float PlayerMaxAbilityStamina = 10.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Ability")
		float PlayerAbilitySlowTimeStrength = 0.7f; 

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Cores")
		float NumOfCores = 0.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Cores")
		float MaxCores = MAX_FLT;
};
