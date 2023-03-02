// Geometry Hell 2. Made By Alexey Guchmazov

#include "Logic/InteractComponent.h"

UInteractComponent::UInteractComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UInteractComponent::OnPlayerInteract()
{
}

void UInteractComponent::BeginPlay()
{
	Super::BeginPlay();
}