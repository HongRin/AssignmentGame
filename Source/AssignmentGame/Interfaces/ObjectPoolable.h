#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ObjectPoolable.generated.h"


UINTERFACE(MinimalAPI)
class UObjectPoolable : public UInterface
{
	GENERATED_BODY()
};

class ASSIGNMENTGAME_API IObjectPoolable
{
	GENERATED_BODY()

public :
	// ��ü�� ������ ���� ���� ��� ����մϴ�.
	virtual int32 GetID() const PURE_VIRTUAL(IObjectPoolable::GetID, return 0; );
	virtual void SetID(int32 id) PURE_VIRTUAL(IObjectPoolable::SetID, );

	// ��Ȱ�� ���� ���θ� ��Ÿ���� ������ ���� ������ / ������
	virtual bool GetCanRecyclable() const PURE_VIRTUAL(IObjectPoolable::GetID, return true; );
	virtual void SetCanRecyclable(bool canRecyclable ) PURE_VIRTUAL(IObjectPoolable::SetCanRecyclable, );

	// ��Ȱ�� �������� ȣ�� �Ǵ� �޼���
	virtual void OnRecycleStart() PURE_VIRTUAL(IObjectPoolable::OnRecycleStart, );
};

