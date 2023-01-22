// Geometry Hell 2. Made By Alexey Guchmazov

#pragma once

#include "CoreMinimal.h"
#include "Weapon/BaseWeapon.h"
#include "ShotgunWeapon.generated.h"


UCLASS()
class GEOMETRYHELL2_API AShotgunWeapon : public ABaseWeapon
{
	GENERATED_BODY()
	

protected:
	virtual void MakeShot() override;

};
