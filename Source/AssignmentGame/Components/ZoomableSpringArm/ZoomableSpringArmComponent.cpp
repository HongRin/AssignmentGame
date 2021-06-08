#include "ZoomableSpringArmComponent.h"

UZoomableSpringArmComponent::UZoomableSpringArmComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// 줌 최소, 최대 거리를 설정합니다.
	SetArmLengthMinMax(100.0f, 400.0f);
}

void UZoomableSpringArmComponent::BeginPlay()
{
	Super::BeginPlay();

	// 목표 거리를 설정합니다.
	TargetArmLength = ArmLengthTarget =
		(MaxArmLength - MinArmLength) * 0.5f;
}

void UZoomableSpringArmComponent::TickComponent(float dt, ELevelTick tickType, FActorComponentTickFunction* thisTickFunction)
{
	Super::TickComponent(dt, tickType, thisTickFunction);

	SmoothZoomSpringArm(dt);
}

void UZoomableSpringArmComponent::SmoothZoomSpringArm(float dt)
{
	TargetArmLength = FMath::FInterpTo(
		TargetArmLength, ArmLengthTarget,
		dt, 5.0f);
}

void UZoomableSpringArmComponent::ZoomCamera(float axis)
{
	ArmLengthTarget += (axis * -5.0f);
	ArmLengthTarget = FMath::Clamp(
		ArmLengthTarget, MinArmLength, MaxArmLength);
}