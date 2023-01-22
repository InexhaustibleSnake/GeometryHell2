// Geometry Hell 2. Made By Alexey Guchmazov

#pragma once

#include "CoreMinimal.h"
#include "Weapon/BaseWeapon.h"
#include "BlasterWeapon.generated.h"


UCLASS()
class GEOMETRYHELL2_API ABlasterWeapon : public ABaseWeapon
{
	GENERATED_BODY()
	
protected:
	virtual void MakeShot() override;   

};
