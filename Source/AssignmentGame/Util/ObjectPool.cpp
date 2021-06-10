#include "ObjectPool.h"

IObjectPoolable* UObjectPool::GetRecycledObject(int32 objId)
{
	// ����� ������ 0 �̶�� �����մϴ�.
	if (PoolObjects.Num() == 0) return nullptr;

	// ���ο� ������Ʈ�� �����մϴ�.
	IObjectPoolable* poolableObj = nullptr;

	// ����� ������ŭ �ݺ��մϴ�.
	for (auto elem : PoolObjects)
	{
		// ������ �����ϸ� ��ϵ� ���̵� ���ٸ�
		if (elem->GetCanRecyclable() && elem->GetID() == objId)
		{
			// ������Ʈ�� ����մϴ�.
			(poolableObj = elem)->SetCanRecyclable(false);
			poolableObj->OnRecycleStart();
			break;
		}
	}

	// �ݺ����� ���� �Ŀ��� ã�� ���ߴٸ� �����մϴ�.
	if (poolableObj == nullptr)
		return nullptr;

	return poolableObj;
}
