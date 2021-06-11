#include "DungeonLevel.h"

#include "Actors/Characters/PlayerCharacter/PlayerCharacter.h"

#include "Single/GameInstance/AGGameInst.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Widgets/CharacterWidget/Player/PlayerWidget.h"

ADungeonLevel::ADungeonLevel()
{
	static ConstructorHelpers::FClassFinder<UPlayerWidget> BP_PLAYER_WIDGET(
		TEXT("WidgetBlueprint'/Game/Blueprints/Widget/BP_PlayerWidget.BP_PlayerWidget_C'"));
	if (BP_PLAYER_WIDGET.Succeeded()) BP_PlayerWidget = BP_PLAYER_WIDGET.Class;
}

void ADungeonLevel::BeginPlay()
{
	Super::BeginPlay();

	PlayerWidget = CreateWidget<UPlayerWidget>(GetWorld(), BP_PlayerWidget);

	PlayerWidget->AddToViewport();
	PlayerWidget->UpdatePlayerHp();
	PlayerWidget->UpdateMoney();
}
