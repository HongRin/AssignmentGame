#include "MonsterAnimInst.h"
#include "Actors/Characters/MonsterCharacter/MonsterCharacter.h"
#include "Actors/Controllers/MonsterController/MonsterController.h"
#include "Components/MonsterAttack/MonsterAttackComponent.h"

void UMonsterAnimInst::NativeUpdateAnimation(float dt)
{
	Super::NativeUpdateAnimation(dt);

	Owner = Cast<AMonsterCharacter>(TryGetPawnOwner());

	if (!IsValid(Owner)) return;

	VelocityLength = Owner->GetVelocity().Size();
}

void UMonsterAnimInst::AnimNotify_UpdateRotation()
{
	Cast<AMonsterController>(Owner->GetController())->IsLookatPlayer();
}

void UMonsterAnimInst::AnimNotify_AttackRange()
{ Owner->GetMonsterAttack()->ActiveMonsterAttackRange(); }

void UMonsterAnimInst::AnimNotify_AttackFin()
{
	if (Owner->GetMonsterAttack()->OnMonsterAttackFinished.IsBound())
		Owner->GetMonsterAttack()->OnMonsterAttackFinished.Broadcast();
}
