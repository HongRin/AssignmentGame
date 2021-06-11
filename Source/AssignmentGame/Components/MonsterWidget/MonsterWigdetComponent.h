#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "MonsterWigdetComponent.generated.h"


UCLASS()
class ASSIGNMENTGAME_API UMonsterWigdetComponent : public UWidgetComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TSubclassOf<class UHpableCharacterWidget> MonsterCharacterWidgetClass;
	
	UPROPERTY()
	class UHpableCharacterWidget* MonsterWidgetInstance;

	UPROPERTY()
	class AMonsterCharacter* MonsterCharacter;

public:
	UMonsterWigdetComponent();

protected:
	virtual void BeginPlay() override;

public:
	class UHpableCharacterWidget* GetMonsterWidgetInstance();

		
};
