// Geometry Hell 2. Made By Alexey Guchmazov

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StartCameraShake.generated.h"

class UBoxComponent;
class UCameraShakeBase;

UCLASS()
class GEOMETRYHELL2_API AStartCameraShake : public AActor
{
	GENERATED_BODY()
	
public:	
	AStartCameraShake();

protected:
	virtual void BeginPlay() override;
	void PlayCameraShake(AActor* Actor);
	void StopCameraShake(AActor* Actor);
	APlayerController* GetPlayerController(AActor* Actor);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UCameraShakeBase> CameraShake;

	UFUNCTION()
		virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		virtual void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
