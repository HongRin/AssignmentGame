#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MonsterInfo.generated.h"

USTRUCT(BlueprintType)
struct ASSIGNMENTGAME_API FMonsterInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	// ���� �ڵ�
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName MonsterCode;

	// ���� �̸�
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText MonsterName;

	// �ִ� ü��
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxHp;

	// ���ݷ�
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Atk;

	// �̵��ӵ�
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MoveSpeed;

	// ���̷�Ż �޽� ���
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FSoftObjectPath SkeletalMeshPath;

	// �ִ� �ν��Ͻ� ���
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FSoftObjectPath AnimInstanceClassPath;

	// ȹ�� ��
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 DropMoney;

	// ����
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Level;
};
