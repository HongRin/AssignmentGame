#include "PlayerAttackComponent.h"
#include "Actors/Characters/PlayerCharacter/PlayerCharacter.h"
#include "Components/MovementHelper/MovementHelperComponent.h"

UPlayerAttackComponent::UPlayerAttackComponent()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AM_ATTACK(
		TEXT("AnimMontage'/Game/Actors/PlayerCharacter/Animations/AM_Attack.AM_Attack'"));
	if (AM_ATTACK.Succeeded()) AttackAnimMontage = AM_ATTACK.Object;
}

void UPlayerAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<APlayerCharacter>(GetOwner());

	OnAttackFinished.AddLambda([this]()->void {
		IsAttack = false;
		PlayerCharacter->GetMovementHelper()->SetIsCanMove(true);
		});
}

void UPlayerAttackComponent::PlayAttack()
{
	if (IsAttack) return;
	IsAttack = true;
	PlayerCharacter->GetMovementHelper()->SetIsCanMove(false);
	PlayerCharacter->PlayAnimMontage(AttackAnimMontage);
}

