#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "PlayerDetectorComponent.generated.h"

UCLASS()
class ASSIGNMENTGAME_API UPlayerDetectorComponent : public USphereComponent
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bDetectPlayer;

private:
	UPlayerDetectorComponent();
	virtual void BeginPlay() override;

private:
	// �÷��̾ ���� ���� �����մϴ�.
	UFUNCTION()
		void OnPlayerDetected(
			UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

	// �÷��̾ �������� ���� �����մϴ�.
	UFUNCTION()
		void OnPlayerLost(
			UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);

public:
	// �÷��̾� ���� ���θ� ��ȯ�մϴ�.
	FORCEINLINE bool IsPlayerDetected() const
	{ return bDetectPlayer; }
};