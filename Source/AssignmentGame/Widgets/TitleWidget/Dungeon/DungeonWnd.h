#pragma once

#include "AssignmentGame.h"
#include "Blueprint/UserWidget.h"
#include "Structures/DungeonInfo/DungeonInfo.h"
#include "DungeonWnd.generated.h"

UCLASS()
class ASSIGNMENTGAME_API UDungeonWnd : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon Code")
	FName Code;

private :
	class UDataTable* DT_DungeonInfo;
	FDungeonInfo* DungeonInfo;

private :
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Name;
	
	UPROPERTY(meta = (BindWidget))
	class UImage* Image_Sprite;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Select;

public :
	UDungeonWnd(const FObjectInitializer& ObjInitializer);

protected:
	virtual void NativeConstruct() override;

private :
	void InitializeDungeonWnd();

public :
	UFUNCTION()
	void OnClickButtonSelect();
};
