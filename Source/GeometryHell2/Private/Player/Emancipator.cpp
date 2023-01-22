// Geometry Hell 2. Made By Alexey Guchmazov

#include "Player/Emancipator.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Player/Components/WeaponComponent.h"

AEmancipator::AEmancipator()
{
	PrimaryActorTick.bCanEverTick = true;

	MainCamera = CreateDefaultSubobject<UCameraComponent>("MainCamera");
	MainCamera->SetupAttachment(GetRootComponent());

	GetMesh()->SetupAttachment(MainCamera);

	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>("UWeaponComponent");
}

void AEmancipator::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEmancipator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEmancipator::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MouseX", this, &AEmancipator::AddControllerYawInput);
	PlayerInputComponent->BindAxis("MouseY", this, &AEmancipator::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("MoveForward", this, &AEmancipator::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AEmancipator::MoveRight);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AEmancipator::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AEmancipator::StopJumping);

	PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent, &UWeaponComponent::NextWeapon);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &UWeaponComponent::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &UWeaponComponent::StopFire);
}

void AEmancipator::MoveForward(float Amount)
{
	AddMovementInput(GetActorForwardVector(), Amount);
}

void AEmancipator::MoveRight(float Amount)
{
	AddMovementInput(GetActorRightVector(), Amount);
}