#include "MonsterAnimInst.h"
#include "Actors/Characters/MonsterCharacter/MonsterCharacter.h"

void UMonsterAnimInst::NativeUpdateAnimation(float dt)
{
	Super::NativeUpdateAnimation(dt);

	Owner = Cast<AMonsterCharacter>(TryGetPawnOwner());

	if (!IsValid(Owner)) return;

	VelocityLength = Owner->GetVelocity().Size();
}
