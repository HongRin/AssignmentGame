#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "ZoomableSpringArmComponent.generated.h"

UCLASS()
class ASSIGNMENTGAME_API UZoomableSpringArmComponent : public USpringArmComponent
{
	GENERATED_BODY()
	
private:
	// 현재 길이
	float ArmLengthTarget;

	// 최소 길이
	float MinArmLength;

	// 최대 길이
	float MaxArmLength;

public:
	UZoomableSpringArmComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent(float dt,
		enum ELevelTick tickType, FActorComponentTickFunction* thisTickFunction) override;

private:
	// 부드럽게 줌이 이루어질수 있도록 합니다.
	void SmoothZoomSpringArm(float dt);

public:
	// 카메라 줌을 수행합니다.
	/// - APlayerCharacter 에서 마우스 휠 입력에 바인딩됩니다.
	void ZoomCamera(float axis);

public:
	// 줌이 가능한 최소, 최대 거리를 설정합니다.
	FORCEINLINE void SetArmLengthMinMax(float min, float max)
	{
		MinArmLength = min;
		MaxArmLength = max;
	}
};
