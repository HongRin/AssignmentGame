#include "PlayerAnimInst.h"
#include "Actors/Characters/PlayerCharacter/PlayerCharacter.h"
#include "Components/MovementHelper/MovementHelperComponent.h"

void UPlayerAnimInst::NativeUpdateAnimation(float dt)
{
	Super::NativeUpdateAnimation(dt);

	Owner = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (!IsValid(Owner)) return;
	
	VelocityLength = Owner->GetVelocity().Size();
	bIsInAir = Owner->GetMovementHelper()->IsInAir();
}
