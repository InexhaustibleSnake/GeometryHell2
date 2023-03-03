// Geometry Hell 2. Made By Alexey Guchmazov

#include "Logic/MainGameInstance.h"

void UMainGameInstance::AddCores(float Amount)
{
	NumOfCores += Amount;
}

void UMainGameInstance::DecreaseCoreAmount(float Amount)
{
	NumOfCores = FMath::Clamp(NumOfCores - Amount, 0.0f, MaxCores);
}