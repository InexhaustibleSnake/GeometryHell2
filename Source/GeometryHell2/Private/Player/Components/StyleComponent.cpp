// Geometry Hell 2. Made By Alexey Guchmazov

#include "Player/Components/StyleComponent.h"
#include "Logic/MainGameInstance.h"

UStyleComponent::UStyleComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UStyleComponent::BeginPlay()
{
	Super::BeginPlay();
	const auto PlayerController = Cast<APlayerController>(GetOwner());
	const auto PlayerPawn = Cast<APawn>(PlayerController->GetPawn());

	PlayerPawn->OnTakeAnyDamage.AddDynamic(this, &UStyleComponent::OnTakeAnyDamage);
}

void UStyleComponent::AddStylePoints(float Amount)
{
	StylePoints = FMath::Clamp(StylePoints + Amount, MinStylePoints, MaxStylePoints);
	IsStyleTypeChanged();
	OnStylePointsChanged.Broadcast();
}

void UStyleComponent::AddCores(float Cores)
{
	auto MainGameInstance = Cast<UMainGameInstance>(GetWorld()->GetGameInstance());
	if (!MainGameInstance) return;

	MainGameInstance->AddCores(Cores * CoreMultiplier);

	if (GetWorld()->GetTimerManager().IsTimerActive(StyleReductionTimer))
	{
		ClearStyleReduceTimer();
	}

	GetWorld()->GetTimerManager().SetTimer(StyleReductionTimer, this, &UStyleComponent::ReduceStylePointsByTimer, StylePointReduceRate, true, StyleReduceDelay);
}

void UStyleComponent::IsStyleTypeChanged()
{
	int32 IntegerStyle = StylePoints;
	switch (static_cast<int32>(StylePoints))
	{
	case 0:
		OnStyleTypeChange.Broadcast(EStyleType::D);
		CoreMultiplier = 1;
		break;
	case 1:
		OnStyleTypeChange.Broadcast(EStyleType::C);
		CoreMultiplier = 2;
		break;
	case 2:
		OnStyleTypeChange.Broadcast(EStyleType::B);
		CoreMultiplier = 3;
		break;
	case 3:
		OnStyleTypeChange.Broadcast(EStyleType::A);
		CoreMultiplier = 4;
		break;
	case 4:
		OnStyleTypeChange.Broadcast(EStyleType::S);
		CoreMultiplier = 5;
		break;
	}
}

void UStyleComponent::ReduceStylePointsByTimer()
{
	StylePoints = FMath::Clamp(StylePoints - StyleReduceAmountByTimer, MinStylePoints, MaxStylePoints);
	IsStyleTypeChanged();
	OnStylePointsChanged.Broadcast();

	if (StylePoints == MinStylePoints)
	{
		ClearStyleReduceTimer();
	}
}

void UStyleComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	StylePoints = FMath::Clamp(StylePoints - StyleReduceAmountByDamage, MinStylePoints, MaxStylePoints);
	IsStyleTypeChanged();
	OnStylePointsChanged.Broadcast();
}

void UStyleComponent::ClearStyleReduceTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(StyleReductionTimer);
}

void UStyleComponent::ClearStylePoints()
{
	StylePoints = MinStylePoints;
}