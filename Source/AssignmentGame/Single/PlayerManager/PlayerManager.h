#pragma once

#include "AssignmentGame.h"
#include "Single/ManagerClass/ManagerClass.h"
#include "PlayerManager.generated.h"

UCLASS()
class ASSIGNMENTGAME_API UPlayerManager : public UManagerClass
{
	GENERATED_BODY()

private :
	// �÷��̾� ĳ����
	UPROPERTY()
	class APlayerCharacter* PlayerCharacter;
	
	// �÷��̾� ��Ʈ�ѷ�
	UPROPERTY()
	class APlayableController* PlayerController;

public:
	// �÷��̾� ��Ʈ�ѷ��� ĳ���͸� ����մϴ�.
	void RegisterPlayer(class APlayerCharacter* newPlayerCharacter, 
		class APlayableController* newPlayerController);

public:
	virtual void InitManagerClass() override;
	virtual void ShutdownManagerClass() override;

public:
	// �÷��̾� ĳ���͸� ����ϴ�.
	FORCEINLINE class APlayerCharacter* GetPlayableCharacter() const
	{ return PlayerCharacter; }

	// �÷��̾� ��Ʈ�ѷ��� ����ϴ�.
	FORCEINLINE class APlayableController* GetPlayableController() const
	{ return PlayerController; }


};
