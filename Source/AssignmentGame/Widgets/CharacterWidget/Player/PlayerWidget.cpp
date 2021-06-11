#include "PlayerWidget.h"
#include "Single/GameInstance/AGGameInst.h"
#include "Single/PlayerManager/PlayerManager.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UPlayerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Text_GameState->SetVisibility(ESlateVisibility::Hidden);

	Time = 5;
}

void UPlayerWidget::UpdatePlayerHp()
{
	ProgressBar_HP->SetPercent(GetManager(UPlayerManager)->GetPlayerInfo()->Hp / GetManager(UPlayerManager)->GetPlayerInfo()->MaxHp);
}

void UPlayerWidget::UpdateMoney()
{
	FText Money = FText::FromString(FString(TEXT("Money : ")) + FString::FromInt(GetManager(UPlayerManager)->GetPlayerInfo()->Money));
	Text_Money->SetText(Money);
}

void UPlayerWidget::PlayGameStateAnimation(bool isClear)
{
	if(isClear)
	Text_GameState->SetText(FText::FromString(FString(TEXT("GameClear"))));
	else
	Text_GameState->SetText(FText::FromString(FString(TEXT("GameOver"))));

	PlayAnimation(GameState);

	FTimerHandle timerHandle;
	GetWorld()->GetTimerManager().SetTimer(
		timerHandle,
		[this]() {
			--Time;
			if (Time == 0)
			{
				GetGameInst(GetWorld())->SetNextLevelName(FName(TEXT("Title")));
				UGameplayStatics::OpenLevel(this, FName(TEXT("Loading")));
			}
		},
		1.0f,
			true);
}
