#include "PlayerCharacter.h"
#include "Components/MovementHelper/MovementHelperComponent.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// 플레이어 팀으로 설정합니다.
	SetGenericTeamId(TEAM_PLAYER);

	// 이 액터의 회전이 컨트롤러의 Yaw 회전을 사용하지 않도록 합니다.
	bUseControllerRotationYaw = false;

	// 이동하는 방향으로 캐릭터를 회전시킵니다.
	GetCharacterMovement()->bOrientRotationToMovement = true;

	// 회전 속도를 지정합니다.
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 450.0f, 0.0f);

	InitializePlayer();
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerCharacter::OnTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	Super::OnTakeDamage(DamagedActor, Damage, DamageType, InstigatedBy, DamageCauser);
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Run"), EInputEvent::IE_Pressed,
		GetMovementHelper(), &UMovementHelperComponent::RunKeyPressed);

	PlayerInputComponent->BindAction(TEXT("Run"), EInputEvent::IE_Released,
		GetMovementHelper(), &UMovementHelperComponent::RunKeyReleased);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed,
		GetMovementHelper(), &UMovementHelperComponent::JumpKeyPressed);

	PlayerInputComponent->BindAxis(TEXT("Horizontal"),
		GetMovementHelper(), &UMovementHelperComponent::InputHorizontal);

	PlayerInputComponent->BindAxis(TEXT("Vertical"),
		GetMovementHelper(), &UMovementHelperComponent::InputVertical);
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

float APlayerCharacter::GetMaxHp()
{
	return 0.0f;
}

float APlayerCharacter::GetHp()
{
	return 0.0f;
}

void APlayerCharacter::SetHp(float value)
{
}

void APlayerCharacter::OnCharacterDie()
{

}

void APlayerCharacter::InitializePlayer()
{
#pragma region Component
	MovementHelper = CreateDefaultSubobject<UMovementHelperComponent>(TEXT("MOVEMENT_HELPER"));
#pragma endregion

}
