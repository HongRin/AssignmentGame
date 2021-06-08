#include "MonsterCharacter.h"

AMonsterCharacter::AMonsterCharacter()
{
	// 몬스터팀으로 설정합니다.
	SetGenericTeamId(TEAM_MONSTER);
}

void AMonsterCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AMonsterCharacter::OnTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	Super::OnTakeDamage(DamagedActor, Damage, DamageType, InstigatedBy, DamageCauser);
}

void AMonsterCharacter::OnCharacterDie()
{
}
