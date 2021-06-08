#include "BaseCharacter.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// 팀이 없도록 설정합니다.
	Team = FGenericTeamId::NoTeam;
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	OnTakeAnyDamage.AddDynamic(this, &ABaseCharacter::OnTakeDamage);
}

void ABaseCharacter::OnTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	SetHp(GetHp() - Damage);

	// Hp 의 값이 0 이하라면
	if (GetHp() <= 0.0f)
	{
		// Hp 를 0.0f 로 설정합니다.
		SetHp(0.0f);
		// 캐릭터의 사망여부를 true로 변경합니다.
		bIsDie = true;
		// 캐릭터 사망 함수를 실행합니다.
		OnCharacterDie();
	}
}

void ABaseCharacter::OnCharacterDie()
{
}

