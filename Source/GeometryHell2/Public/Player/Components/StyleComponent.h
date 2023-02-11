// Geometry Hell 2. Made By Alexey Guchmazov

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StyleComponent.generated.h"

UENUM(BlueprintType)
enum class EStyleType : uint8
{
	D,
	C,
	B,
	A,
	S
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStylePointsChanged);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStyleTypeChange, EStyleType, StyleType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GEOMETRYHELL2_API UStyleComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStyleComponent();
	void AddStylePoints(float Amount);
	void AddCores(float Cores);
	void ClearStylePoints();

	UFUNCTION(BlueprintCallable)
		float GetStylePoints() const { return StylePoints; }

	UFUNCTION(BlueprintCallable)
		float GetStylePercent() const { return StylePoints / MaxStylePoints; }

	UPROPERTY(BlueprintAssignable)
		FOnStylePointsChanged OnStylePointsChanged;

	UPROPERTY(BlueprintAssignable)
		FOnStyleTypeChange OnStyleTypeChange;

protected:
	virtual void BeginPlay() override;
	void ReduceStylePointsByTimer();
	void ClearStyleReduceTimer();

	UFUNCTION()
		void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION()
		void IsStyleTypeChanged();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "StylePointsReduce")
		float StylePointReduceRate = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "StylePointsReduce")
		float StyleReduceDelay = 6.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "StylePointsReduce")
		float StyleReduceAmountByTimer = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "StylePointsReduce")
		float StyleReduceAmountByDamage = 0.25f;

	EStyleType StyleType;

	float StylePoints = 0.0f;
	float MaxStylePoints = 4.0f;
	float MinStylePoints = 0.0f;

	int32 CoreMultiplier = 1;

	class UMainGameInstance* GameInstance;

	FTimerHandle StyleReductionTimer;
};
