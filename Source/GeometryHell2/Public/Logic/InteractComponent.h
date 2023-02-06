// Geometry Hell 2. Made By Alexey Guchmazov

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteract);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GEOMETRYHELL2_API UInteractComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInteractComponent();

	UFUNCTION(BlueprintCallable)
		virtual void OnPlayerInteract();

	UPROPERTY(BlueprintAssignable)
		FOnInteract OnInteract;

protected:
	virtual void BeginPlay() override;
};
