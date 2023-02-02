// Geometry Hell 2. Made By Alexey Guchmazov

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MainSaveGame.generated.h"

USTRUCT(BlueprintType)
struct FActorsData
{
	GENERATED_USTRUCT_BODY()

public:

		FTransform ActorTransform;
	
};

UCLASS()
class GEOMETRYHELL2_API UMainSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UMainSaveGame();
	
	UPROPERTY(EditAnywhere)
	FVector PlayerLocation;
};
