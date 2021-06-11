#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerWidget.generated.h"

UCLASS()
class ASSIGNMENTGAME_API UPlayerWidget : public UUserWidget
{
	GENERATED_BODY()
		
private :
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Money;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_GameState;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* ProgressBar_HP;
	
	UPROPERTY(meta = (BindWidgetAnim))
	class UWidgetAnimation* GameState;

	int32 Time;

protected:
	virtual void NativeConstruct() override;

public :
	void UpdatePlayerHp();
	void UpdateMoney();

public :
	void PlayGameStateAnimation(bool isClear);

};
