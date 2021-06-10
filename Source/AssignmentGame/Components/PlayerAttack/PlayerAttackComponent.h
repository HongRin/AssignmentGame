#pragma once

#include "AssignmentGame.h"
#include "Components/ActorComponent.h"
#include "PlayerAttackComponent.generated.h"


DECLARE_MULTICAST_DELEGATE(OnAttackEventSignatue);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ASSIGNMENTGAME_API UPlayerAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public :
	OnAttackEventSignatue OnAttackFinished;

private :
	UPROPERTY()
	TSubclassOf<class ABullet> BP_Bullet;

	class UAnimMontage* AttackAnimMontage;
	class APlayerCharacter* PlayerCharacter;

	UPROPERTY()
	class UObjectPool* BulletObjectPool;

private :
	bool IsAttack;

public:	
	UPlayerAttackComponent();

protected:
	virtual void BeginPlay() override;

public :
	void PlayAttack();
	void CreateBullet();
		
};
