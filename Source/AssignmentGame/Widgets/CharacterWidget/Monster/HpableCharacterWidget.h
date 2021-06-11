#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HpableCharacterWidget.generated.h"

UCLASS()
class ASSIGNMENTGAME_API UHpableCharacterWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY()
	class ABaseCharacter* OwnerCharacter;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Name;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* ProgressBar_HP;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Level;

protected :
	virtual void NativeConstruct() override;

public:
	void SetNameText(FText value);
	void InitializeWidget(class ABaseCharacter* ownerCharacter);
	void UpdateHp();
	void SetLevelText(int value);
};
