#include "BaseCharacter.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// ���� ������ �����մϴ�.
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

	// Hp �� ���� 0 ���϶��
	if (GetHp() <= 0.0f)
	{
		// Hp �� 0.0f �� �����մϴ�.
		SetHp(0.0f);
		// ĳ������ ������θ� true�� �����մϴ�.
		bIsDie = true;
		// ĳ���� ��� �Լ��� �����մϴ�.
		OnCharacterDie();
	}
}

void ABaseCharacter::OnCharacterDie()
{
}

