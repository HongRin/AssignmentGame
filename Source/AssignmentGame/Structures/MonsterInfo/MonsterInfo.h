#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MonsterInfo.generated.h"

USTRUCT(BlueprintType)
struct ASSIGNMENTGAME_API FMonsterInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	// 몬스터 코드
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName MonsterCode;

	// 몬스터 이름
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText MonsterName;

	// 최대 체력
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxHp;

	// 공격력
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Atk;

	// 이동속도
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MoveSpeed;

	// 스켈레탈 메쉬 경로
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FSoftObjectPath SkeletalMeshPath;

	// 애님 인스턴스 경로
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FSoftObjectPath AnimInstanceClassPath;

	// 획득 돈
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 DropMoney;

	// 레벨
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Level;
};
