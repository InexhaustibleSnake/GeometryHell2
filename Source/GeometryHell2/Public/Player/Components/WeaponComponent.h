// Geometry Hell 2. Made By Alexey Guchmazov

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

class ABaseWeapon;

USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		TSubclassOf<ABaseWeapon> WeaponClass;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GEOMETRYHELL2_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWeaponComponent();

	virtual void StartFire();
	void StopFire();

	void NextWeapon();

protected:
	virtual void BeginPlay() override;

	int32 CurrentWeaponIndex = 0;

	ABaseWeapon* CurrentWeapon = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
     	TArray<FWeaponData> WeaponData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	    FName WeaponSocketName = "GripPoint";

private:

	void EquipWeapon(int32 WeaponIndex);
	void AttachWeaponToSocket(FName& SocketName, ABaseWeapon* Weapon, USceneComponent* SceneComponent);
};
