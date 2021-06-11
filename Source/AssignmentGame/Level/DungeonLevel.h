#pragma once

#include "AssignmentGame.h"
#include "Engine/LevelScriptActor.h"
#include "DungeonLevel.generated.h"

UCLASS()
class ASSIGNMENTGAME_API ADungeonLevel : public ALevelScriptActor
{
	GENERATED_BODY()

private:
	TArray<class AMonsterCharacter*> MonsterCharacters;

public:
	ADungeonLevel();

	bool DungeonClear();

protected:
	virtual void BeginPlay() override;
	
public:
	FORCEINLINE void AddMonsterCharacters(class AMonsterCharacter* monsterCharacter)
	{ MonsterCharacters.Add(monsterCharacter); }

	FORCEINLINE void RemoveMonsterCharacters(class AMonsterCharacter* monsterCharacter)
	{ MonsterCharacters.Remove(monsterCharacter); };
};
