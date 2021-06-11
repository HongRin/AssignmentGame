#pragma once

#include "AssignmentGame.h"
#include "Engine/LevelScriptActor.h"
#include "DungeonLevel.generated.h"

UCLASS()
class ASSIGNMENTGAME_API ADungeonLevel : public ALevelScriptActor
{
	GENERATED_BODY()

private:
	TSubclassOf<class UPlayerWidget> BP_PlayerWidget;
	class UPlayerWidget* PlayerWidget;

public:
	ADungeonLevel();

protected:
	virtual void BeginPlay() override;
	
};
