#pragma once

#include "CoreMinimal.h"
#include "Actors/Characters/BaseCharacter.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class ASSIGNMENTGAME_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

private :
	// 캐릭터의 이동을 담당하는 컴포넌트
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UMovementHelperComponent* MovementHelper;
	
	// 캐릭터의 줌을 담당하는 컴포넌트
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UZoomableSpringArmComponent* ZoomableSpringArm;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UPlayerAttackComponent* PlayerAttack;

private:
	TSubclassOf<class UPlayerWidget> BP_PlayerWidget;
	class UPlayerWidget* PlayerWidget;

public :
	APlayerCharacter();

protected :
	virtual void BeginPlay() override;

	virtual void OnTakeDamage(
		AActor* DamagedActor,
		float Damage,
		const class UDamageType* DamageType,
		class AController* InstigatedBy,
		AActor* DamageCauser) override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;

	virtual float GetMaxHp() override;
	virtual float GetHp() override;
	virtual void SetHp(float value) override;

	virtual void OnCharacterDie() override;

private :
	void InitializePlayer();

public :
	FORCEINLINE class UMovementHelperComponent* GetMovementHelper()
	{ return MovementHelper; }

	FORCEINLINE class UZoomableSpringArmComponent* GetZoomableSpringArm() const
	{ return ZoomableSpringArm; }

	FORCEINLINE class UPlayerAttackComponent* GetPlayerAttack() const
	{ return PlayerAttack; }
};
