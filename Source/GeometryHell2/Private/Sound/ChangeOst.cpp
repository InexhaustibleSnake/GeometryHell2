// Geometry Hell 2. Made By Alexey Guchmazov

#include "Sound/ChangeOst.h"
#include "Components/BoxComponent.h"
#include "Player/MainPlayerController.h"
#include "GameFramework/Pawn.h"

AChangeOst::AChangeOst()
{
	PrimaryActorTick.bCanEverTick = false;
	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
}

void AChangeOst::BeginPlay()
{
	Super::BeginPlay();	

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AChangeOst::OnPlayerOverlap);
}

void AChangeOst::OnPlayerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto PlayerPawn = Cast<APawn>(OtherActor);
	if (!PlayerPawn) return;

	auto PlayerController = Cast<AMainPlayerController>(PlayerPawn->GetController());
	if (!PlayerController) return;

	if (OverrideAmbient)
	{
		PlayerController->SetAmbient(Ambient, PlayNewAmbient);
	}

	if (OverrideBattleOst)
	{
		PlayerController->SetFightOst(FightOst, PlayNewFightOst);
	}

	Destroy();
}
