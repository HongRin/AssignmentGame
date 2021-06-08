#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "DungeonInfo.generated.h"

USTRUCT(BlueprintType)
struct ASSIGNMENTGAME_API FDungeonInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public :
	// ���� �ڵ�
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName DungeonCode;

	// ���� �̸�
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText DungeonName;

	// ���� �̹��� ���
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FSoftObjectPath DungeonImagePath;
};
