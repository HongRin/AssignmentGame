#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "DungeonInfo.generated.h"

USTRUCT(BlueprintType)
struct ASSIGNMENTGAME_API FDungeonInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public :
	// 던전 코드
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName DungeonCode;

	// 던전 이름
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText DungeonName;

	// 던전 이미지 경로
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FSoftObjectPath DungeonImagePath;
};
