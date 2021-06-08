#pragma once

#include "AssignmentGame.h"
#include "GameFramework/Character.h"
#include "GenericTeamAgentInterface.h"
#include "BaseCharacter.generated.h"

// 캐릭터들의 기본 베이스를 담고 있는 클래스입니다.

UCLASS()
class ASSIGNMENTGAME_API ABaseCharacter : 
	public ACharacter,
	public IGenericTeamAgentInterface
{
	GENERATED_BODY()

protected :
	FGenericTeamId Team;

	// 캐릭터의 사망여부를 나타냅니다.
	UPROPERTY()
	bool bIsDie;

public:
	ABaseCharacter();

protected:
	virtual void BeginPlay() override;

public :
	// MaxHp 를 얻습니다.
	virtual float GetMaxHp() PURE_VIRTUAL(ABaseCharacter::GetMaxHp, return 0.0f;);
	// Hp 를 얻습니다.
	virtual float GetHp() PURE_VIRTUAL(ABaseCharacter::GetHp, return 0.0f;);
	// Hp 를 설정합니다.
	virtual void SetHp(float value) PURE_VIRTUAL(ABaseCharacter::SetHp, );

protected :
	// 캐릭터가 데미지를 입었을 때 실행하는 함수입니다.
	UFUNCTION()
	virtual void OnTakeDamage(
		AActor* DamagedActor,
		float Damage,
		const class UDamageType* DamageType,
		class AController* InstigatedBy,
		AActor* DamageCauser);

	// 캐릭터가 죽을 때 실행하는 함수입니다.
	virtual void OnCharacterDie();

public :
	// 캐릭터의 사망여부를 확인하는 메서드입니다.
	FORCEINLINE bool IsDie() const
	{ return bIsDie; }


	// 팀을 설정합니다.
	FORCEINLINE virtual void SetGenericTeamId(const FGenericTeamId& TeamID)
	{ Team = TeamID; }

	// 팀 ID 를 가져옵니다.
	FORCEINLINE virtual FGenericTeamId GetGenericTeamId() const
	{ return Team; }
};
