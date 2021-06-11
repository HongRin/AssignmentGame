#include "PlayerWidget.h"
#include "Single/GameInstance/AGGameInst.h"
#include "Single/PlayerManager/PlayerManager.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UPlayerWidget::NativeConstruct()
{
	Super::NativeConstruct();
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
