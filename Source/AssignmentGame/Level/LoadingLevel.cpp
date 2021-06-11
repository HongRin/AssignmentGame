#include "LoadingLevel.h"
#include "UserWidget.h"
#include "Engine/World.h"

ALoadingLevel::ALoadingLevel()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> BP_LOADING(
		TEXT("WidgetBlueprint'/Game/Blueprints/Widget/BP_Loading.BP_Loading_C'"));
	if (BP_LOADING.Succeeded()) BP_Loading = BP_LOADING.Class;
}

void ALoadingLevel::BeginPlay()
{
	Super::BeginPlay();

	CreateWidget<UUserWidget>(GetWorld(), BP_Loading)->AddToViewport();
}
