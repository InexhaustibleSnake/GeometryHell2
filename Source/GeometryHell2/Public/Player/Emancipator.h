// Geometry Hell 2. Made By Alexey Guchmazov

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Emancipator.generated.h"

class USkeletalMeshComponent;
class UCameraComponent;
class UWeaponComponent;
class UHealthComponent;
class UAbilityComponent;
class UStaminaComponent;

UCLASS()
class GEOMETRYHELL2_API AEmancipator : public ACharacter
{
	GENERATED_BODY()

public:
	AEmancipator();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UCameraComponent* MainCamera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
        UWeaponComponent* WeaponComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UAbilityComponent* AbilityComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaminaComponent* StaminaComponent;

private:
	void MoveForward(float Amount);
	void MoveRight(float Amount);
	void Interact();
};
