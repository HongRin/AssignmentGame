#include "ObjectPool.h"

IObjectPoolable* UObjectPool::GetRecycledObject(int32 objId)
{
	// 요소의 개수가 0 이라면 리턴합니다.
	if (PoolObjects.Num() == 0) return nullptr;

	// 새로운 오브젝트를 생성합니다.
	IObjectPoolable* poolableObj = nullptr;

	// 요소의 개수만큼 반복합니다.
	for (auto elem : PoolObjects)
	{
		// 재사용이 가능하며 등록된 아이디가 같다면
		if (elem->GetCanRecyclable() && elem->GetID() == objId)
		{
			// 오브젝트를 등록합니다.
			(poolableObj = elem)->SetCanRecyclable(false);
			poolableObj->OnRecycleStart();
			break;
		}
	}

	// 반복문이 끝난 후에도 찾지 못했다면 리턴합니다.
	if (poolableObj == nullptr)
		return nullptr;

	return poolableObj;
}
