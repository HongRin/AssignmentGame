#pragma once

#include "AssignmentGame.h"

#include "Engine/GameInstance.h"

#include "AGGameInst.generated.h"

#ifndef GAME_INST
#define GAME_INST
#define GetGameInst(worldContextObj) (Cast<UAGGameInst>(worldContextObj->GetGameInstance()))
#endif


UCLASS()
class ASSIGNMENTGAME_API UAGGameInst : public UGameInstance
{
	GENERATED_BODY()
	
private :
	// �������� �ε��� ���� �̸��� �����մϴ�.
	FName NextLevelName;

public:
	virtual void Init() override;
	virtual void Shutdown() override;

public:
	// ���� ������ �����մϴ�.
	FORCEINLINE void SetNextLevelName(FName nextLevelName)
	{ NextLevelName = nextLevelName; }


	// ���� ���� �̸��� ����ϴ�.
	UFUNCTION(BlueprintCallable)
	FORCEINLINE FName GetNextLevelName() const
	{ return NextLevelName; }
};
