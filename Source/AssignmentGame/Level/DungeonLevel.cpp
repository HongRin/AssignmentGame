#include "DungeonLevel.h"
#include "Actors/Characters/PlayerCharacter/PlayerCharacter.h"

#include "Single/GameInstance/AGGameInst.h"
#include "Single/PlayerManager/PlayerManager.h"

ADungeonLevel::ADungeonLevel()
{

}

bool ADungeonLevel::DungeonClear()
{
	// ĳ���Ͱ� ���� �ʾҰ� ���� ������ ���� 0 �̶�� Ŭ�����մϴ�.
	return (MonsterCharacters.Num() == 0 || GetManager(UPlayerManager)->GetPlayableCharacter()->IsDied());
}

void ADungeonLevel::BeginPlay()
{
	Super::BeginPlay();


}
