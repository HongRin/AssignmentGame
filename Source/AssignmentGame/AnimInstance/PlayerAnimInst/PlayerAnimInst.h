#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInst.generated.h"

UCLASS()
class ASSIGNMENTGAME_API UPlayerAnimInst : public UAnimInstance
{
	GENERATED_BODY()
	
private:
	class APlayerCharacter* Owner;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float VelocityLength;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsInAir;

public :
	virtual void NativeUpdateAnimation(float dt) override;

private :
	UFUNCTION()
	void AnimNotify_FireBullet();

	UFUNCTION()
	void AnimNotify_AttackFin();

	UFUNCTION()
	void AnimNotify_UpdateRotation();
};
