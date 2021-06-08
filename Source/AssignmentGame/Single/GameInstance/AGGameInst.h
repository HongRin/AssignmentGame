#pragma once

#include "AssignmentGame.h"

#include "Engine/GameInstance.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"

#include "Single/ManagerClass/ManagerClass.h"

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

	// ����� �Ŵ��� Ŭ���� �ν��Ͻ��� �����մϴ�.
	TMap<FString, UManagerClass*> ManagerClasses;

public:
	virtual void Init() override;
	virtual void Shutdown() override;

private:
	// ManagerClass �� ��Ͻ�ŵ�ϴ�.
	void RegisterManagerClass(TSubclassOf<UManagerClass> managerClass);

public:
	// ���� ������ �����մϴ�.
	FORCEINLINE void SetNextLevelName(FName nextLevelName)
	{ NextLevelName = nextLevelName; }

	// ���� ���� �̸��� ����ϴ�.
	UFUNCTION(BlueprintCallable)
	FORCEINLINE FName GetNextLevelName() const
	{ return NextLevelName; }

	// ����� ManagerClass �� ����ϴ�.
	template<typename ManagerClassType>
	FORCEINLINE ManagerClassType* GetManagerClass()
	{return Cast<ManagerClassType>(ManagerClasses[ManagerClassType::StaticClass()->GetName()]);}

	// �ּ� �ε��� ���� StreamableManager �� ��� �޼���
	template<>
	FORCEINLINE FStreamableManager* GetManagerClass<FStreamableManager>()
	{return &UAssetManager::GetStreamableManager();}


};
