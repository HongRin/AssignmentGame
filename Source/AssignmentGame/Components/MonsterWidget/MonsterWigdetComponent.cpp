#include "MonsterWigdetComponent.h"
#include "Actors/Characters/MonsterCharacter/MonsterCharacter.h"

#include "Widgets/CharacterWidget/Monster/HpableCharacterWidget.h"

#include "Single/GameInstance/AGGameInst.h"
#include "Single/PlayerManager/PlayerManager.h"


UMonsterWigdetComponent::UMonsterWigdetComponent()
{
	static ConstructorHelpers::FClassFinder<UHpableCharacterWidget> WIDGET_BP_Monster(
		TEXT("WidgetBlueprint'/Game/Blueprints/Widget/BP_MonsterWidget.BP_MonsterWidget_C'"));
	if (WIDGET_BP_Monster.Succeeded())
		MonsterCharacterWidgetClass = WIDGET_BP_Monster.Class;
	else
		UE_LOG(LogTemp, Error, TEXT("MonsterWidgetComponent.cpp::%d::LINE::WIDGET_BP_ENEMY is not loaded!"), __LINE__);


	if (IsValid(MonsterCharacterWidgetClass))
	{
		SetWidgetClass(MonsterCharacterWidgetClass);
		SetDrawSize(FVector2D(100.0f, 60.0f));
	}
}

void UMonsterWigdetComponent::BeginPlay()
{
	Super::BeginPlay();

	MonsterCharacter = Cast<AMonsterCharacter>(GetOwner());

	SetWidgetSpace(EWidgetSpace::Screen);

	SetRelativeLocation(FVector::UpVector * 70.0F);
}

UHpableCharacterWidget* UMonsterWigdetComponent::GetMonsterWidgetInstance()
{
	return MonsterWidgetInstance = IsValid(MonsterWidgetInstance) ?
		MonsterWidgetInstance :
		Cast<UHpableCharacterWidget>(GetUserWidgetObject());
}

