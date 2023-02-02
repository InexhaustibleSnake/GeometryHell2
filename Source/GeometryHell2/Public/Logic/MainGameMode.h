// Geometry Hell 2. Made By Alexey Guchmazov

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainGameMode.generated.h"

UCLASS()
class GEOMETRYHELL2_API AMainGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	void SaveGame();
	void LoadGame();
};
