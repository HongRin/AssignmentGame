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
	// 다음으로 로드할 레벨 이름을 저장합니다.
	FName NextLevelName;

public:
	virtual void Init() override;
	virtual void Shutdown() override;

public:
	// 다음 레벨을 설정합니다.
	FORCEINLINE void SetNextLevelName(FName nextLevelName)
	{ NextLevelName = nextLevelName; }


	// 다음 레벨 이름을 얻습니다.
	UFUNCTION(BlueprintCallable)
	FORCEINLINE FName GetNextLevelName() const
	{ return NextLevelName; }
};
