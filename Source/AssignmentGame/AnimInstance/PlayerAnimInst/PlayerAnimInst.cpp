#include "PlayerAnimInst.h"
#include "Actors/Characters/PlayerCharacter/PlayerCharacter.h"
#include "Components/MovementHelper/MovementHelperComponent.h"
#include "Components/PlayerAttack/PlayerAttackComponent.h"

void UPlayerAnimInst::NativeUpdateAnimation(float dt)
{
	Super::NativeUpdateAnimation(dt);

	Owner = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (!IsValid(Owner)) return;
	
	VelocityLength = Owner->GetVelocity().Size();
	bIsInAir = Owner->GetMovementHelper()->IsInAir();
}

void UPlayerAnimInst::AnimNotify_FireBullet()
{
	Owner->GetPlayerAttack()->CreateBullet();
}

void UPlayerAnimInst::AnimNotify_AttackFin()
{
	if (Owner->GetPlayerAttack()->OnAttackFinished.IsBound())
		Owner->GetPlayerAttack()->OnAttackFinished.Broadcast();
}
