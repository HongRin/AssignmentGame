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
	class UProgressBar* ProgressBar_HP;
	
protected:
	virtual void NativeConstruct() override;

public :
	void UpdatePlayerHp();
	void UpdateMoney();
};
