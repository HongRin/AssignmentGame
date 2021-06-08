#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ManagerClass.generated.h"


// ManagerClass Type �� ��ü�� �����ϰ� �ҷ��� �� �ִ� ��ũ��
#ifndef MANAGER_INSTANCE
#define MANAGER_INSTANCE
#define GetManager(ManagerClassType) (GetGameInst(GetWorld())->GetManagerClass<ManagerClassType>())
#endif

UCLASS(Abstract)
class ASSIGNMENTGAME_API UManagerClass : public UObject
{
	GENERATED_BODY()
	
public:
	// �Ŵ��� Ŭ���� ���
	FORCEINLINE virtual void InitManagerClass() {};
	FORCEINLINE virtual void ShutdownManagerClass() {};
};
