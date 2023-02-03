// Geometry Hell 2. Made By Alexey Guchmazov

#include "Enemy/BaseAIController.h"
#include "Enemy/BaseEnemy.h"
#include "Perception/AIPerceptionComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/Emancipator.h"
#include "Player/MainPlayerController.h"

ABaseAIController::ABaseAIController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("AIPerceptionComponent");
	SetPerceptionComponent(*AIPerceptionComponent);
}

void ABaseAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    const auto Enemy = Cast<ABaseEnemy>(InPawn);
    if (Enemy)
    {
        RunBehaviorTree(Enemy->BehaviorTreeAsset);
        Enemy->OnDeath.AddUObject(this, &ABaseAIController::OnDestroy);
    }
}

void ABaseAIController::BeginPlay()
{
    Super::BeginPlay();
    Player = Cast<AEmancipator>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

    GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &ABaseAIController::ActorsUpdated);
}

void ABaseAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (!SpotPlayer) return;
    SetFocus(Player);
}

void ABaseAIController::ActorsUpdated(TArray<AActor*> const& UpdatedActors)
{
    for (auto PerceivedActor : UpdatedActors)
    {
        if (PerceivedActor == Player)
        {       
            if (!SpotPlayer)
            {
                SpotPlayer = true;
                const auto EnemyOwner = Cast<ABaseEnemy>(GetPawn());
                EnemyOwner->ShootStart();
                UpdateEnemiesInFight(1);
            }
        }
    }
}

void ABaseAIController::UpdateEnemiesInFight(int32 Amount)
{
    auto PlayerController = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
    if (!PlayerController) return;
    PlayerController->UpdateEnemiesInFight(Amount);
}

void ABaseAIController::OnDestroy()
{
    UpdateEnemiesInFight(-1);
    Destroy();
}