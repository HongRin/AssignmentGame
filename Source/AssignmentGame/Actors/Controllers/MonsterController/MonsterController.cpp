#include "MonsterController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

AMonsterController::AMonsterController()
{
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI_PERCEPTION")));

	SetGenericTeamId(TEAM_MONSTER);

	{
		AISightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SIGHT_CONFIG"));

		AISightConfig->SightRadius = 400.0f;
		AISightConfig->LoseSightRadius = AISightConfig->SightRadius + 100.0f;
		AISightConfig->PeripheralVisionAngleDegrees = 180.0f;

		// 감지 객체가 사라지더라도 유지하는 시간
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
}

void AMonsterController::Tick(float dt)
{
	Super::Tick(dt);
}
