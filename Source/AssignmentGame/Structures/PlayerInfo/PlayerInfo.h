#pragma once

#include "CoreMinimal.h"
#include "PlayerInfo.generated.h"

USTRUCT()
struct ASSIGNMENTGAME_API FPlayerInfo
{

	GENERATED_USTRUCT_BODY()

public :
	// �ִ� ü��
	UPROPERTY()
	float MaxHp;

	// ���� ü��
	UPROPERTY()
	float Hp;

	// ���ݷ�
	UPROPERTY()
	float Atk;

	// �ȱ� �ӵ�
	UPROPERTY()
	float WalkSpeed;

	// �޸��� �ӵ�
	UPROPERTY()
	float RunSpeed;

	// ������
	UPROPERTY()
	int32 Money;

public:
	FPlayerInfo();
};
