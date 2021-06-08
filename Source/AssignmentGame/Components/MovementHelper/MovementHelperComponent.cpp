#include "MovementHelperComponent.h"
#include "Actors/Characters/PlayerCharacter/PlayerCharacter.h"
#include "Single/GameInstance/AGGameInst.h"
#include "Single/PlayerManager/PlayerManager.h"

void UMovementHelperComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<APlayerCharacter>(GetOwner());

	PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed = 
		GetManager(UPlayerManager)->GetPlayerInfo()->WalkSpeed;

	// 공중에서 캐릭터를 80% 제어 가능하도록 합니다.
	PlayerCharacter->GetCharacterMovement()->AirControl = 0.8f;

	// 캐릭터가 받는 중력 설정
	PlayerCharacter->GetCharacterMovement()->GravityScale = 2.5f;

	// 점프 초기 가속력 설정
	PlayerCharacter->GetCharacterMovement()->JumpZVelocity = 1000.0f;
}

bool UMovementHelperComponent::IsInAir() const
{
	return IsValid(PlayerCharacter) ?
		PlayerCharacter->GetCharacterMovement()->IsFalling() : true;
}

void UMovementHelperComponent::RunKeyPressed()
{
	PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed =
		GetManager(UPlayerManager)->GetPlayerInfo()->RunSpeed;
}

void UMovementHelperComponent::RunKeyReleased()
{
	PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed = 
		GetManager(UPlayerManager)->GetPlayerInfo()->WalkSpeed; 
}

void UMovementHelperComponent::JumpKeyPressed()
{ PlayerCharacter->Jump(); }

void UMovementHelperComponent::InputHorizontal(float axis)
{
	// 컨트롤러 회전중 Yaw 회전만을 저장합니다.
	FRotator yawRotation(0.0f, PlayerCharacter->GetControlRotation().Yaw, 0.0f);

	// 컨트롤러 기준 오른쪽 방향을 저장합니다.
	FVector rightVector = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);
	// FRotationMatrix : 회전된 좌표계 정보를 저장하는 행렬을 나타냅니다.
	// GetUnitAxis(EAxis) : EAxis 축으로의 방향을 반환합니다.

	PlayerCharacter->AddMovementInput(rightVector, axis);
}

void UMovementHelperComponent::InputVertical(float axis)
{
	// 컨트롤러 회전중 Yaw 회전만을 저장합니다.
	FRotator yawRotation(0.0f, PlayerCharacter->GetControlRotation().Yaw, 0.0f);

	// 컨트롤러 기준 앞 방향을 저장합니다.
	FVector forwardVector = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);

	PlayerCharacter->AddMovementInput(forwardVector, axis);
}

