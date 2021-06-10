#pragma once

#include "CoreMinimal.h"
#include "Interfaces/ObjectPoolable.h"
#include "ObjectPool.generated.h"


UCLASS()
class ASSIGNMENTGAME_API UObjectPool : public UObject
{
	GENERATED_BODY()

private :
	// Ǯ���� ������Ʈ���� ������ �迭
	TArray<IObjectPoolable*> PoolObjects;

public :
	// ���ο� ������Ʈ�� ����մϴ�. 
	template<typename T>
	T* RegisterRecyclableObject(T* newRecyclableObject)
	{
		PoolObjects.Add((IObjectPoolable*)newRecyclableObject);
		return newRecyclableObject;
	}

	// ����� ��ü�� ����ϴ�.
	IObjectPoolable* GetRecycledObject(int32 objId);

};
