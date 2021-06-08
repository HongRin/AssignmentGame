#include "AssignmentGameGameModeBase.h"
#include "Actors/Characters/PlayerCharacter/PlayerCharacter.h"
#include "Actors/Controllers/PlayerController/PlayableController.h"

AAssignmentGameGameModeBase::AAssignmentGameGameModeBase()
{
	DefaultPawnClass = APlayerCharacter::StaticClass();
	PlayerControllerClass = APlayableController::StaticClass();
}