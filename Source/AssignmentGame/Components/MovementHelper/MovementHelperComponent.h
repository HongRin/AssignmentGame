#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MovementHelperComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ASSIGNMENTGAME_API UMovementHelperComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	class APlayerCharacter* PlayerCharacter;

	bool IsCanMove;

protected:
	virtual void BeginPlay() override;

public:
	bool IsInAir() const;

public:
	void RunKeyPressed();
	void RunKeyReleased();

	void JumpKeyPressed();

	void InputHorizontal(float axis);
	void InputVertical(float axis);

	void Attack();

	FORCEINLINE void SetIsCanMove(bool isCanMove)
	{ IsCanMove = isCanMove; }
};
