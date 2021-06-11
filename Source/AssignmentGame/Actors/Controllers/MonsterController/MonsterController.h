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

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UBehaviorTree* MonsterBehaviorTree;

	UPROPERTY()
	class AActor* TrackingTargetActor;

	UPROPERTY()
	class AMonsterCharacter* MonsterCharacter;

public:
	AMonsterController();

public:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float dt) override;

private:
	void TrackingPlayer();

	bool IsPlayerNearby();

public:
	void IsLookatPlayer();

private:
	UFUNCTION()
	void OnSightDetected(AActor* Actor, FAIStimulus Stimulus);

public :
	FORCEINLINE class AMonsterCharacter* GetMonsterCharacter() const
	{ return MonsterCharacter; }
};
