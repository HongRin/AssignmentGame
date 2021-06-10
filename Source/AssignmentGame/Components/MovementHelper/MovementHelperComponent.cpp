#include "MovementHelperComponent.h"
#include "Actors/Characters/PlayerCharacter/PlayerCharacter.h"
#include "Components/PlayerAttack/PlayerAttackComponent.h"
#include "Single/GameInstance/AGGameInst.h"
#include "Single/PlayerManager/PlayerManager.h"

void UMovementHelperComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<APlayerCharacter>(GetOwner());

	PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed = 
		GetManager(UPlayerManager)->GetPlayerInfo()->WalkSpeed;

	// ���߿��� ĳ���͸� 80% ���� �����ϵ��� �մϴ�.
	PlayerCharacter->GetCharacterMovement()->AirControl = 0.8f;

	// ĳ���Ͱ� �޴� �߷� ����
	PlayerCharacter->GetCharacterMovement()->GravityScale = 2.5f;

	// ���� �ʱ� ���ӷ� ����
	PlayerCharacter->GetCharacterMovement()->JumpZVelocity = 1000.0f;

	IsCanMove = true;
}

bool UMovementHelperComponent::IsInAir() const
{
	return IsValid(PlayerCharacter) ?
		PlayerCharacter->GetCharacterMovement()->IsFalling() : true;
}

void UMovementHelperComponent::RunKeyPressed()
{
	if (!IsCanMove) return;
	PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed =
		GetManager(UPlayerManager)->GetPlayerInfo()->RunSpeed;
}

void UMovementHelperComponent::RunKeyReleased()
{
	if (!IsCanMove) return;
	PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed = 
		GetManager(UPlayerManager)->GetPlayerInfo()->WalkSpeed; 
}

void UMovementHelperComponent::JumpKeyPressed()
{ 
	if (!IsCanMove) return;
	PlayerCharacter->Jump(); 
}

void UMovementHelperComponent::InputHorizontal(float axis)
{
	if (!IsCanMove) return;
	// ��Ʈ�ѷ� ȸ���� Yaw ȸ������ �����մϴ�.
	FRotator yawRotation(0.0f, PlayerCharacter->GetControlRotation().Yaw, 0.0f);

	// ��Ʈ�ѷ� ���� ������ ������ �����մϴ�.
	FVector rightVector = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);
	// FRotationMatrix : ȸ���� ��ǥ�� ������ �����ϴ� ����� ��Ÿ���ϴ�.
	// GetUnitAxis(EAxis) : EAxis �������� ������ ��ȯ�մϴ�.

	PlayerCharacter->AddMovementInput(rightVector, axis);
}

void UMovementHelperComponent::InputVertical(float axis)
{
	if (!IsCanMove) return;

	// ��Ʈ�ѷ� ȸ���� Yaw ȸ������ �����մϴ�.
	FRotator yawRotation(0.0f, PlayerCharacter->GetControlRotation().Yaw, 0.0f);

	// ��Ʈ�ѷ� ���� �� ������ �����մϴ�.
	FVector forwardVector = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);

	PlayerCharacter->AddMovementInput(forwardVector, axis);
}

void UMovementHelperComponent::Attack()
{ 
	if (IsInAir() && !IsCanMove) return;
	PlayerCharacter->GetPlayerAttack()->PlayAttack(); 
}

