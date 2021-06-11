#pragma once

#include "AssignmentGame.h"
#include "Engine/LevelScriptActor.h"
#include "LoadingLevel.generated.h"

UCLASS()
class ASSIGNMENTGAME_API ALoadingLevel : public ALevelScriptActor
{
	GENERATED_BODY()
	
private:
	TSubclassOf<class UUserWidget> BP_Loading;

public:
	ALoadingLevel();

protected:
	virtual void BeginPlay() override;
};
