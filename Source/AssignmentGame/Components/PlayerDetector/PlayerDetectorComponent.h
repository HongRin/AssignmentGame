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
	// 플레이어가 들어온 것을 감지합니다.
	UFUNCTION()
		void OnPlayerDetected(
			UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

	// 플레이어가 빠져나간 것을 감지합니다.
	UFUNCTION()
		void OnPlayerLost(
			UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);

public:
	// 플레이어 감지 여부를 반환합니다.
	FORCEINLINE bool IsPlayerDetected() const
	{ return bDetectPlayer; }
};
