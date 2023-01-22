// Geometry Hell 2. Made By Alexey Guchmazov

#include "Weapon/BaseWeapon.h"
#include "GameFramework/Pawn.h"

ABaseWeapon::ABaseWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);
}

void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();

}

void ABaseWeapon::StartFire()
{
	GetWorldTimerManager().SetTimer(FireTimer, this, &ABaseWeapon::MakeShot, WeaponParams.FireRate, true, 0.0f);
}

void ABaseWeapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(FireTimer);
}

void ABaseWeapon::MakeShot()
{

}

void ABaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd)
{
	FVector ViewLocation;
	FRotator ViewRotation;

	GetPlayerController()->GetPlayerViewPoint(ViewLocation, ViewRotation);

	const auto HalfRad = FMath::DegreesToRadians(WeaponParams.Accuracy);
	const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad);

	TraceStart = ViewLocation;
	TraceEnd = ViewLocation + ShootDirection * TraceMaxDistance;
}

void ABaseWeapon::MakeTrace(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd)
{
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);
}

const AController* ABaseWeapon::GetPlayerController()
{
	const auto Pawn = Cast<APawn>(GetOwner());
	return Pawn ? Pawn->GetController() : nullptr;
}

FVector ABaseWeapon::GetMuzzleWorldLocation()
{
	return WeaponMesh->GetSocketLocation("Muzzle");
}
