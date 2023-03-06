// Geometry Hell 2. Made By Alexey Guchmazov

#include "Sound/ChangeOst.h"
#include "Components/BoxComponent.h"
#include "Player/MainPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Player/Components/MasterAudioComponent.h"

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
	const auto PlayerPawn = Cast<APawn>(OtherActor);
	if (!PlayerPawn) return;

	const auto PlayerController = Cast<AMainPlayerController>(PlayerPawn->GetController());
	if (!PlayerController) return;

	auto MasterAudioComponent = PlayerController->FindComponentByClass<UMasterAudioComponent>();
	if (!MasterAudioComponent) return;

	if (OverrideAmbient)
	{
		MasterAudioComponent->SetAmbient(Ambient, PlayNewAmbient);
	}

	if (OverrideBattleOst)
	{
		MasterAudioComponent->SetFightOst(FightOst, PlayNewFightOst);
	}

	Destroy();
}
