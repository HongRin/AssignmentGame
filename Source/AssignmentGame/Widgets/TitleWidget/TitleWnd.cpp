#include "TitleWnd.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"

void UTitleWnd::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Start->OnClicked.AddDynamic(this, &UTitleWnd::OnClickButtonStart);
	HorizontalBox_List->SetVisibility(ESlateVisibility::Hidden);
	IsListView = false;
}

void UTitleWnd::OnClickButtonStart()
{
	if (IsListView)
	{
		HorizontalBox_List->SetVisibility(ESlateVisibility::Hidden);
		IsListView = false;
	}
	else
	{
		HorizontalBox_List->SetVisibility(ESlateVisibility::Visible);
		IsListView = true;
	}
}
