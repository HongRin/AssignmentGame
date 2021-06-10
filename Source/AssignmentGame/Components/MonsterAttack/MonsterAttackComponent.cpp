#include "MonsterAttackComponent.h"
#include "Actors/Characters/MonsterCharacter/MonsterCharacter.h"


UMonsterAttackComponent::UMonsterAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	MonsterCharacter = Cast<AMonsterCharacter>(GetOwner());
}

void UMonsterAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void UMonsterAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

