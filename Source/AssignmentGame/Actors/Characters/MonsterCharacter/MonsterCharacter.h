#pragma once

#include "Actors/Characters/BaseCharacter.h"
#include "Structures/MonsterInfo/MonsterInfo.h"
#include "MonsterCharacter.generated.h"

UCLASS()
class ASSIGNMENTGAME_API AMonsterCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
private :
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Basic", meta = (AllowPrivateAccess = "true"))
	class UMonsterAttackComponent* MonsterAttack;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Basic", meta = (AllowPrivateAccess = "true"))
	class UPlayerDetectorComponent* PlayerDetector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic", meta = (AllowPrivateAccess = "true"))
	float MaxHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic", meta = (AllowPrivateAccess = "true"))
	float Hp;

	// 몬스터 코드
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Basic", meta = (AllowPrivateAccess = "true"))
	FName MonsterCode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic", meta = (AllowPrivateAccess = "true"))
	float Atk;

	UPROPERTY()
	class UAGGameInst* GameInst;

	// 몬스터 데이터 테이블
	UPROPERTY()
	class UDataTable* DT_MonsterInfo;

	// 몬스터 정보
	FMonsterInfo MonsterInfo;

public:
	AMonsterCharacter();

protected:
	virtual void BeginPlay() override;

	virtual void OnTakeDamage(
		AActor* DamagedActor,
		float Damage,
		const class UDamageType* DamageType,
		class AController* InstigatedBy,
		AActor* DamageCauser) override;

private:
	// SkeletalMesh 정보 초기화
	void InitializeSkeletalMeshComponent();

public:
	// 몬스터 정보 초기화
	UFUNCTION(BlueprintCallable)
		void InitializeMonsterDataConstructTime();

public:
	FORCEINLINE virtual float GetMaxHp() override
	{ return MaxHp; }
	FORCEINLINE virtual float GetHp() override
	{ return Hp; }
	FORCEINLINE virtual void SetHp(float value) override
	{ Hp = value; }

	virtual void OnCharacterDie() override;
};
