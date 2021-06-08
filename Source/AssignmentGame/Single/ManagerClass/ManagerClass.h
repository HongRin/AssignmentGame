#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ManagerClass.generated.h"


// ManagerClass Type 의 객체를 간편하게 불러올 수 있는 매크로
#ifndef MANAGER_INSTANCE
#define MANAGER_INSTANCE
#define GetManager(ManagerClassType) (GetGameInst(GetWorld())->GetManagerClass<ManagerClassType>())
#endif

UCLASS(Abstract)
class ASSIGNMENTGAME_API UManagerClass : public UObject
{
	GENERATED_BODY()
	
public:
	// 매니저 클래스 등록
	FORCEINLINE virtual void InitManagerClass() {};
	FORCEINLINE virtual void ShutdownManagerClass() {};
};
