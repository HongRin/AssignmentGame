#include "TitleLevel.h"
#include "UserWidget.h"

#include "Single/GameInstance/AGGameInst.h"
#include "Single/PlayerManager/PlayerManager.h"

ATitleLevel::ATitleLevel()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> BP_TITLE_WND(
		TEXT("WidgetBlueprint'/Game/Blueprints/Widget/BP_TitleWnd.BP_TitleWnd_C'"));
	if (BP_TITLE_WND.Succeeded()) BP_TitleWnd = BP_TITLE_WND.Class;
}

void ATitleLevel::BeginPlay()
{
	CreateWidget<UUserWidget>(GetWorld(), BP_TitleWnd)->AddToViewport();

	GetManager(UPlayerManager)->GetPlayerInfo()->Hp = GetManager(UPlayerManager)->GetPlayerInfo()->MaxHp;
}
