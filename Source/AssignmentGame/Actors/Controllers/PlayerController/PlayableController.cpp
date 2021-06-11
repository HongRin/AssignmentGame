#include "PlayableController.h"
#include "Actors/Characters/PlayerCharacter/PlayerCharacter.h"
#include "Single/GameInstance/AGGameInst.h"
#include "Single/PlayerManager/PlayerManager.h"

APlayableController::APlayableController()
{
}

void APlayableController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis(TEXT("MouseX"), this, &APlayableController::InputMouseX);
	InputComponent->BindAxis(TEXT("MouseY"), this, &APlayableController::InputMouseY);
}

void APlayableController::OnPossess(APawn* aPawn)
{ 
	Super::OnPossess(aPawn); 

	GetManager(UPlayerManager)->RegisterPlayer(Cast<APlayerCharacter>(aPawn), this);
}

void APlayableController::InputMouseX(float axis)
{ AddYawInput(axis); }

void APlayableController::InputMouseY(float axis)
{ AddPitchInput(axis); }
