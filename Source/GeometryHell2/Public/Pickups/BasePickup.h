// Geometry Hell 2. Made By Alexey Guchmazov

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePickup.generated.h"

class USphereComponent;

UCLASS()
class GEOMETRYHELL2_API ABasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	ABasePickup();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		USphereComponent* SphereComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Respawn")
		bool ShouldRespawn = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Respawn")
		float RespawnTime = 15.0f;

	virtual bool GivePickup(AActor* PlayerPawn);
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

private:
	FTimerHandle RespawnTimer;

	void PickupTaken();
	void RespawnPickup();
};
