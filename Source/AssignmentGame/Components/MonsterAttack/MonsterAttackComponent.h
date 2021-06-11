#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MonsterAttackComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnMonsterAttackEventSignature)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ASSIGNMENTGAME_API UMonsterAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	FOnMonsterAttackEventSignature OnMonsterAttackFinished;

private :
	UPROPERTY()
	class AMonsterCharacter* MonsterCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character", meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* MonsterAttack;

	UPROPERTY()
	bool AttackState;

public:	
	UMonsterAttackComponent();

protected:
	virtual void BeginPlay() override;

public:
	void PlayMonsterAttackAnimation();

	void ActiveMonsterAttackRange();

public :
	FORCEINLINE bool IsMonsterAttacking() const
	{ return AttackState; };
};
