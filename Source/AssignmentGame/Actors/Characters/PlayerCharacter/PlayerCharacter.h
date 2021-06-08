#pragma once

#include "CoreMinimal.h"
#include "Actors/Characters/BaseCharacter.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class ASSIGNMENTGAME_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
private :
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UMovementHelperComponent* MovementHelper;

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
};
