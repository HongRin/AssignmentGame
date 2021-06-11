#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TitleWnd.generated.h"

UCLASS()
class ASSIGNMENTGAME_API UTitleWnd : public UUserWidget
{
	GENERATED_BODY()
	
private :
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Start;

	UPROPERTY(meta = (BindWidget))
	class UHorizontalBox* HorizontalBox_List;

	bool IsListView;

protected :
	virtual void NativeConstruct() override;

public :
	UFUNCTION()
	void OnClickButtonStart();


};
