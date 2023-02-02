// Geometry Hell 2. Made By Alexey Guchmazov

#include "Logic/MainGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Logic/MainSaveGame.h"
#include "GameFramework/Character.h"

void AMainGameMode::SaveGame()
{
	UMainSaveGame* SaveGameInstance = Cast<UMainSaveGame>(UGameplayStatics::CreateSaveGameObject(UMainSaveGame::StaticClass()));

	AActor* Player = Cast<AActor>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	SaveGameInstance->PlayerLocation = Player->GetActorLocation();

	UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("Slot"), 0);
	
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Game Saved"));
}

void AMainGameMode::LoadGame()
{
	UMainSaveGame* SaveGameInstance = Cast<UMainSaveGame>(UGameplayStatics::CreateSaveGameObject(UMainSaveGame::StaticClass()));
	SaveGameInstance = Cast<UMainSaveGame>(UGameplayStatics::LoadGameFromSlot("Slot", 0));

	AActor* Player = Cast<AActor>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	Player->SetActorLocation(SaveGameInstance->PlayerLocation);

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Load Saved"));
}