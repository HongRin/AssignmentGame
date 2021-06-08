#include "PlayerManager.h"
#include "Actors/Characters/PlayerCharacter/PlayerCharacter.h"
#include "Actors/Controllers/PlayerController/PlayableController.h"

void UPlayerManager::RegisterPlayer(APlayerCharacter* newPlayerCharacter, APlayableController* newPlayerController)
{
	PlayerCharacter = newPlayerCharacter;
	PlayerController = newPlayerController;
}

void UPlayerManager::InitManagerClass()
{}

void UPlayerManager::ShutdownManagerClass()
{}
