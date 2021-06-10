#include "MonsterController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

#include "Single/GameInstance/AGGameInst.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

AMonsterController::AMonsterController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT_MONSTER(
		TEXT("BehaviorTree'/Game/AI/BT_Monster.BT_Monster'"));
	if (BT_MONSTER.Succeeded()) MonsterBehaviorTree = BT_MONSTER.Object;



	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI_PERCEPTION")));

	SetGenericTeamId(TEAM_MONSTER);

	{
		AISightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SIGHT_CONFIG"));

		AISightConfig->SightRadius = 400.0f;
		AISightConfig->LoseSightRadius = AISightConfig->SightRadius + 100.0f;
		AISightConfig->PeripheralVisionAngleDegrees = 180.0f;

		// ���� ��ü�� ��������� �����ϴ� �ð�
		AISightConfig->SetMaxAge(2.0f);

		AISightConfig->DetectionByAffiliation.bDetectEnemies = true;
		AISightConfig->DetectionByAffiliation.bDetectFriendlies = false;
		AISightConfig->DetectionByAffiliation.bDetectNeutrals = false;

		GetPerceptionComponent()->ConfigureSense(*AISightConfig);
	}
}

void AMonsterController::BeginPlay()
{
	Super::BeginPlay();
}

void AMonsterController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (IsValid(MonsterBehaviorTree))
	{
		RunBehaviorTree(MonsterBehaviorTree);
		GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this,
			&AMonsterController::OnSightDetected);
	}
	else
		UE_LOG(LogTemp, Error,
			TEXT("MonsterController.cpp :: %d LINE :: MonseterBehaviorTree is not loaded !"), __LINE__);
}

void AMonsterController::Tick(float dt)
{
	Super::Tick(dt);

	TrackingPlayer();
}

void AMonsterController::TrackingPlayer()
{
	if (!IsValid(TrackingTargetActor)) return;

	GetBlackboardComponent()->SetValueAsBool(TEXT("IsTracking"), true);

	MoveToActor(TrackingTargetActor);
}

void AMonsterController::OnSightDetected(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed())
	{
		if (!IsValid(TrackingTargetActor))
			TrackingTargetActor = Actor;
	}
	else
		TrackingTargetActor = nullptr;
}