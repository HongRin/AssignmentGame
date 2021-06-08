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
	// 다음으로 로드할 레벨 이름을 저장합니다.
	FName NextLevelName;

	// 등록한 매니저 클래스 인스턴스를 저장합니다.
	TMap<FString, UManagerClass*> ManagerClasses;

public:
	virtual void Init() override;
	virtual void Shutdown() override;

private:
	// ManagerClass 를 등록시킵니다.
	void RegisterManagerClass(TSubclassOf<UManagerClass> managerClass);

public:
	// 다음 레벨을 설정합니다.
	FORCEINLINE void SetNextLevelName(FName nextLevelName)
	{ NextLevelName = nextLevelName; }

	// 다음 레벨 이름을 얻습니다.
	UFUNCTION(BlueprintCallable)
	FORCEINLINE FName GetNextLevelName() const
	{ return NextLevelName; }

	// 등록한 ManagerClass 를 얻습니다.
	template<typename ManagerClassType>
	FORCEINLINE ManagerClassType* GetManagerClass()
	{return Cast<ManagerClassType>(ManagerClasses[ManagerClassType::StaticClass()->GetName()]);}

	// 애셋 로딩을 위한 StreamableManager 를 얻는 메서드
	template<>
	FORCEINLINE FStreamableManager* GetManagerClass<FStreamableManager>()
	{return &UAssetManager::GetStreamableManager();}


};
