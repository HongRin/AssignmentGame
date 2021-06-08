#pragma once

#include "AssignmentGame.h"
#include "GameFramework/PlayerController.h"
#include "PlayableController.generated.h"

UCLASS()
class ASSIGNMENTGAME_API APlayableController : public APlayerController
{
	GENERATED_BODY()

public :
	APlayableController();

protected:
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* aPawn) override;

private:
	void InputMouseX(float axis);
	void InputMouseY(float axis);
};
