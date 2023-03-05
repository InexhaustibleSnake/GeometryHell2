// Geometry Hell 2. Made By Alexey Guchmazov

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MainGameInstance.generated.h"

UCLASS()
class GEOMETRYHELL2_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void AddCores(float Amount);

	UFUNCTION(BlueprintCallable)
	void DecreaseCoreAmount(float Amount);

	UFUNCTION(BlueprintCallable)
	float GetCores() const { return NumOfCores; }

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Cores")
		float NumOfCores = 0.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Cores")
		float MaxCores = MAX_FLT;
};
