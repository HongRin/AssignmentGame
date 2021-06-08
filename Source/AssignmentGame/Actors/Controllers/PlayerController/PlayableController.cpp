#include "PlayableController.h"

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
{ Super::OnPossess(aPawn); }

void APlayableController::InputMouseX(float axis)
{ AddYawInput(axis); }

void APlayableController::InputMouseY(float axis)
{ AddPitchInput(axis); }
