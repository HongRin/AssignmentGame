#pragma once

#include "AssignmentGame.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "MonsterController.generated.h"

UCLASS()
class ASSIGNMENTGAME_API AMonsterController : public AAIController
{
	GENERATED_BODY()
	
private :
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UAISenseConfig_Sight* AISightConfig;

public:
	AMonsterController();

public:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float dt) override;
};
