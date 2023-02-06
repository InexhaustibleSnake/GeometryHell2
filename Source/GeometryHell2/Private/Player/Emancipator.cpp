// Geometry Hell 2. Made By Alexey Guchmazov

#include "Player/Emancipator.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Player/Components/WeaponComponent.h"
#include "Player/Components/HealthComponent.h"
#include "Player/Components/AbilityComponent.h"
#include "Player/Components/StaminaComponent.h"
#include "Logic/MainGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Logic/InteractComponent.h"
#include "DrawDebugHelpers.h"

AEmancipator::AEmancipator()
{
	PrimaryActorTick.bCanEverTick = true;

	MainCamera = CreateDefaultSubobject<UCameraComponent>("MainCamera");
	MainCamera->SetupAttachment(GetRootComponent());

	GetMesh()->SetupAttachment(MainCamera);
	GetMesh()->CastShadow = false;

	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>("UWeaponComponent");
	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
	AbilityComponent = CreateDefaultSubobject<UAbilityComponent>("AbilityComponent");
	StaminaComponent = CreateDefaultSubobject<UStaminaComponent>("StaminaComponent");
}

void AEmancipator::BeginPlay()
{
	Super::BeginPlay();
	
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

	DECLARE_DELEGATE_OneParam(FAbilityComponentSignature, bool);
	PlayerInputComponent->BindAction<FAbilityComponentSignature>("SlowTime", IE_Pressed, AbilityComponent, &UAbilityComponent::TimeManager, false);
	PlayerInputComponent->BindAction<FAbilityComponentSignature>("StopTime", IE_Pressed, AbilityComponent, &UAbilityComponent::TimeManager, true);
	PlayerInputComponent->BindAction("SlowTime", IE_Released, AbilityComponent, &UAbilityComponent::RestoreTime);
	PlayerInputComponent->BindAction("StopTime", IE_Released, AbilityComponent, &UAbilityComponent::RestoreTime);
	PlayerInputComponent->BindAction("Dash", IE_Pressed, AbilityComponent, &UAbilityComponent::Dash);

	PlayerInputComponent->BindAction("StartSprinting", IE_Pressed, StaminaComponent, &UStaminaComponent::StartSprinting);
	PlayerInputComponent->BindAction("StartSprinting", IE_Released, StaminaComponent, &UStaminaComponent::StopSprinting);

	PlayerInputComponent->BindAction("SaveGame", IE_Released, this, &AEmancipator::SaveGame);
	PlayerInputComponent->BindAction("LoadGame", IE_Released, this, &AEmancipator::LoadGame);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AEmancipator::Interact);
}

void AEmancipator::MoveForward(float Amount)
{
	AddMovementInput(GetActorForwardVector(), Amount);
}

void AEmancipator::MoveRight(float Amount)
{
	AddMovementInput(GetActorRightVector(), Amount);
}

void AEmancipator::Interact()
{
	FVector TraceStart, TraceEnd;
	FRotator TraceRotation;
	GetController()->GetPlayerViewPoint(TraceStart, TraceRotation);
	TraceEnd = TraceStart + TraceRotation.Vector() * 400.0f;
	FHitResult HitResult;
	//DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 2.0f, 0.0f, 3.0f);
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility);
	if (HitResult.bBlockingHit)
	{
		auto InteractComponent = Cast<UInteractComponent>(HitResult.Actor->GetComponentByClass(UInteractComponent::StaticClass()));
		InteractComponent->OnInteract.Broadcast();
	}
}

void AEmancipator::SaveGame()
{
	auto GameModeInstance = Cast<AMainGameMode>(GetWorld()->GetAuthGameMode());
	GameModeInstance->SaveGame();
}

void AEmancipator::LoadGame()
{
	auto GameModeInstance = Cast<AMainGameMode>(GetWorld()->GetAuthGameMode());
	GameModeInstance->LoadGame();
}
