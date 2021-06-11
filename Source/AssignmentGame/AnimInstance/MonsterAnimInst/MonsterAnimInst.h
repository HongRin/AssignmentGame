#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MonsterAnimInst.generated.h"

UCLASS()
class ASSIGNMENTGAME_API UMonsterAnimInst : public UAnimInstance
{
	GENERATED_BODY()
	
private :
	class AMonsterCharacter* Owner;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float VelocityLength;

public:
	virtual void NativeUpdateAnimation(float dt) override;

private:
	UFUNCTION()
	void AnimNotify_UpdateRotation();

	UFUNCTION()
	void AnimNotify_AttackRange();

	UFUNCTION()
	void AnimNotify_AttackFin();
};
