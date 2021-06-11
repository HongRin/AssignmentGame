#include "DungeonWnd.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

#include "Single/GameInstance/AGGameInst.h"
#include "Single/PlayerManager/PlayerManager.h"


UDungeonWnd::UDungeonWnd(const FObjectInitializer& ObjInitializer) :
	Super(ObjInitializer)
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_DUNGEON_INFO(
		TEXT("DataTable'/Game/DataTable/DT_DungeonInfo.DT_DungeonInfo'"));
	if (DT_DUNGEON_INFO.Succeeded()) DT_DungeonInfo = DT_DUNGEON_INFO.Object;
}

void UDungeonWnd::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeDungeonWnd();

	Button_Select->OnClicked.AddDynamic(this, &UDungeonWnd::OnClickButtonSelect);
}

void UDungeonWnd::InitializeDungeonWnd()
{
	FString contextString;
	DungeonInfo = DT_DungeonInfo->FindRow<FDungeonInfo>(Code, contextString);

	Text_Name->SetText(DungeonInfo->DungeonName);
	
	UTexture2D* dungeonImage =
		Cast<UTexture2D>(GetManager(FStreamableManager)->LoadSynchronous(DungeonInfo->DungeonImagePath));

	Image_Sprite->SetBrushFromTexture(dungeonImage);
}

void UDungeonWnd::OnClickButtonSelect()
{
	GetGameInst(GetWorld())->SetNextLevelName(FName(*DungeonInfo->DungeonName.ToString()));
	UGameplayStatics::OpenLevel(this, FName(TEXT("Loading")));
}
