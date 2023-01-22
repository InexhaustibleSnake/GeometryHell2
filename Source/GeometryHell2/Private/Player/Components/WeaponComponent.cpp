// Geometry Hell 2. Made By Alexey Guchmazov

#include "Player/Components/WeaponComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Weapon/BaseWeapon.h"
#include "GameFramework/Character.h"

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;


}

void UWeaponComponent::StartFire()
{
	CurrentWeapon->StartFire();
}

void UWeaponComponent::StopFire()
{
	CurrentWeapon->StopFire();
}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	EquipWeapon(CurrentWeaponIndex);
}

void UWeaponComponent::NextWeapon()
{
	CurrentWeaponIndex = (CurrentWeaponIndex + 1) % WeaponData.Num();
	EquipWeapon(CurrentWeaponIndex);
}

void UWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
	if (WeaponIndex < 0 || WeaponIndex > WeaponData.Num())
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid weapon index"));
		return;
	}

	ACharacter* PlayerCharacter = Cast<ACharacter>(GetOwner());
	if (!PlayerCharacter) return;

	if (CurrentWeapon) CurrentWeapon->Destroy();

	CurrentWeapon = GetWorld()->SpawnActor<ABaseWeapon>(WeaponData[WeaponIndex].WeaponClass);
	CurrentWeapon->SetOwner(GetOwner());

	AttachWeaponToSocket(WeaponSocketName, CurrentWeapon, PlayerCharacter->GetMesh());
}

void UWeaponComponent::AttachWeaponToSocket(FName& SocketName, ABaseWeapon* Weapon, USceneComponent* SceneComponent)
{
	if (!Weapon && !SceneComponent) return;

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}


