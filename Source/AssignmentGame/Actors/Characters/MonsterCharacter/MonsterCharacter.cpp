#include "MonsterCharacter.h"

AMonsterCharacter::AMonsterCharacter()
{
	// ���������� �����մϴ�.
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
