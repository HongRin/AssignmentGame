#pragma once

#include "AssignmentGame.h"
#include "Engine/LevelScriptActor.h"
#include "TitleLevel.generated.h"

UCLASS()
class ASSIGNMENTGAME_API ATitleLevel : public ALevelScriptActor
{
	GENERATED_BODY()

private:
	TSubclassOf<class UUserWidget> BP_TitleWnd;

public:
	ATitleLevel();

protected:
	virtual void BeginPlay() override;
	
};
