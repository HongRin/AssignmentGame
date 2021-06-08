#pragma once

#include "CoreMinimal.h"
#include "PlayerInfo.generated.h"

USTRUCT()
struct ASSIGNMENTGAME_API FPlayerInfo
{

	GENERATED_USTRUCT_BODY()

public :
	// 최대 체력
	UPROPERTY()
	float MaxHp;

	// 현재 체력
	UPROPERTY()
	float Hp;

	// 공격력
	UPROPERTY()
	float Atk;

	// 걷기 속도
	UPROPERTY()
	float WalkSpeed;

	// 달리기 속도
	UPROPERTY()
	float RunSpeed;

	// 소지금
	UPROPERTY()
	int32 Money;

public:
	FPlayerInfo();
};
