#include "DungeonLevel.h"
#include "Actors/Characters/PlayerCharacter/PlayerCharacter.h"

#include "Single/GameInstance/AGGameInst.h"
#include "Single/PlayerManager/PlayerManager.h"

ADungeonLevel::ADungeonLevel()
{

}

bool ADungeonLevel::DungeonClear()
{
	// 캐릭터가 죽지 않았고 남은 몬스터의 수가 0 이라면 클리어합니다.
	return (MonsterCharacters.Num() == 0 || GetManager(UPlayerManager)->GetPlayableCharacter()->IsDied());
}

void ADungeonLevel::BeginPlay()
{
	Super::BeginPlay();


}
