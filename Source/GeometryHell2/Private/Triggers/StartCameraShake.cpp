// Geometry Hell 2. Made By Alexey Guchmazov

#include "Triggers/StartCameraShake.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraShakeBase.h"

AStartCameraShake::AStartCameraShake()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	BoxCollision->SetupAttachment(GetRootComponent());
}

void AStartCameraShake::BeginPlay()
{
	Super::BeginPlay();
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AStartCameraShake::BeginOverlap);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &AStartCameraShake::EndOverlap);
}

void AStartCameraShake::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	PlayCameraShake(OtherActor);
}

void AStartCameraShake::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	StopCameraShake(OtherActor);
}

void AStartCameraShake::PlayCameraShake(AActor* Actor)
{
	const auto Controller = GetPlayerController(Actor);

	if (Controller && Controller->PlayerCameraManager)
	{
		Controller->PlayerCameraManager->StartCameraShake(CameraShake);
	}
}

void AStartCameraShake::StopCameraShake(AActor* Actor)
{
	const auto Controller = GetPlayerController(Actor);

	if (Controller && Controller->PlayerCameraManager)
	{
		Controller->PlayerCameraManager->StopAllCameraShakes(true);
	}
}

APlayerController* AStartCameraShake::GetPlayerController(AActor* Actor)
{
	const auto PlayerPawn = Cast<APawn>(Actor);
	if (!PlayerPawn) return nullptr;

	const auto PlayerController = PlayerPawn->GetController<APlayerController>();
	if (!PlayerController) return nullptr;

	return PlayerController;
}
