#pragma once

#include "AssignmentGame.h"
#include "GameFramework/Character.h"
#include "GenericTeamAgentInterface.h"
#include "BaseCharacter.generated.h"

// ĳ���͵��� �⺻ ���̽��� ��� �ִ� Ŭ�����Դϴ�.

UCLASS()
class ASSIGNMENTGAME_API ABaseCharacter : 
	public ACharacter,
	public IGenericTeamAgentInterface
{
	GENERATED_BODY()

protected :
	FGenericTeamId Team;

	// ĳ������ ������θ� ��Ÿ���ϴ�.
	UPROPERTY()
	bool bIsDie;

public:
	ABaseCharacter();

protected:
	virtual void BeginPlay() override;

public :
	// MaxHp �� ����ϴ�.
	virtual float GetMaxHp() PURE_VIRTUAL(ABaseCharacter::GetMaxHp, return 0.0f;);
	// Hp �� ����ϴ�.
	virtual float GetHp() PURE_VIRTUAL(ABaseCharacter::GetHp, return 0.0f;);
	// Hp �� �����մϴ�.
	virtual void SetHp(float value) PURE_VIRTUAL(ABaseCharacter::SetHp, );

protected :
	// ĳ���Ͱ� �������� �Ծ��� �� �����ϴ� �Լ��Դϴ�.
	UFUNCTION()
	virtual void OnTakeDamage(
		AActor* DamagedActor,
		float Damage,
		const class UDamageType* DamageType,
		class AController* InstigatedBy,
		AActor* DamageCauser);

	// ĳ���Ͱ� ���� �� �����ϴ� �Լ��Դϴ�.
	virtual void OnCharacterDie();

public :
	// ĳ������ ������θ� Ȯ���ϴ� �޼����Դϴ�.
	FORCEINLINE bool IsDie() const
	{ return bIsDie; }


	// ���� �����մϴ�.
	FORCEINLINE virtual void SetGenericTeamId(const FGenericTeamId& TeamID)
	{ Team = TeamID; }

	// �� ID �� �����ɴϴ�.
	FORCEINLINE virtual FGenericTeamId GetGenericTeamId() const
	{ return Team; }
};
