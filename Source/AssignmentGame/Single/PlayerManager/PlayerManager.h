#pragma once

#include "AssignmentGame.h"
#include "Single/ManagerClass/ManagerClass.h"
#include "PlayerManager.generated.h"

UCLASS()
class ASSIGNMENTGAME_API UPlayerManager : public UManagerClass
{
	GENERATED_BODY()

private :
	// 플레이어 캐릭터
	UPROPERTY()
	class APlayerCharacter* PlayerCharacter;
	
	// 플레이어 컨트롤러
	UPROPERTY()
	class APlayableController* PlayerController;

public:
	// 플레이어 컨트롤러와 캐릭터를 등록합니다.
	void RegisterPlayer(class APlayerCharacter* newPlayerCharacter, 
		class APlayableController* newPlayerController);

public:
	virtual void InitManagerClass() override;
	virtual void ShutdownManagerClass() override;

public:
	// 플레이어 캐릭터를 얻습니다.
	FORCEINLINE class APlayerCharacter* GetPlayableCharacter() const
	{ return PlayerCharacter; }

	// 플레이어 컨트롤러를 얻습니다.
	FORCEINLINE class APlayableController* GetPlayableController() const
	{ return PlayerController; }


};
