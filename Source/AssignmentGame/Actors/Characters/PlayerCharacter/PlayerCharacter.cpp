#include "PlayerCharacter.h"
#include "Components/MovementHelper/MovementHelperComponent.h"
#include "Components/ZoomableSpringArm/ZoomableSpringArmComponent.h"
#include "Components/PlayerAttack/PlayerAttackComponent.h"
#include "AnimInstance/PlayerAnimInst/PlayerAnimInst.h"
#include "Single/GameInstance/AGGameInst.h"
#include "Single/PlayerManager/PlayerManager.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// �÷��̾� ������ �����մϴ�.
	SetGenericTeamId(TEAM_PLAYER);

	// �� ������ ȸ���� ��Ʈ�ѷ��� Yaw ȸ���� ������� �ʵ��� �մϴ�.
	bUseControllerRotationYaw = false;

	// �̵��ϴ� �������� ĳ���͸� ȸ����ŵ�ϴ�.
	GetCharacterMovement()->bOrientRotationToMovement = true;

	// ȸ�� �ӵ��� �����մϴ�.
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 450.0f, 0.0f);

	InitializePlayer();

	Tags.Add(TEXT("Player"));
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerCharacter::OnTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	Super::OnTakeDamage(DamagedActor, Damage, DamageType, InstigatedBy, DamageCauser);

	UE_LOG(LogTemp, Warning, TEXT("Player::MaxHp[%.1f]::Hp[%.1f]"), GetMaxHp(), GetHp());
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

	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed,
		GetMovementHelper(), &UMovementHelperComponent::Attack);

	PlayerInputComponent->BindAxis(TEXT("Horizontal"),
		GetMovementHelper(), &UMovementHelperComponent::InputHorizontal);

	PlayerInputComponent->BindAxis(TEXT("Vertical"),
		GetMovementHelper(), &UMovementHelperComponent::InputVertical);

	PlayerInputComponent->BindAxis(TEXT("MouseWheel"),
		GetZoomableSpringArm(), &UZoomableSpringArmComponent::ZoomCamera);
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

float APlayerCharacter::GetMaxHp()
{
	return GetManager(UPlayerManager)->GetPlayerInfo()->MaxHp;
}

float APlayerCharacter::GetHp()
{
	return GetManager(UPlayerManager)->GetPlayerInfo()->Hp;
}

void APlayerCharacter::SetHp(float value)
{ GetManager(UPlayerManager)->GetPlayerInfo()->Hp -= value; }

void APlayerCharacter::OnCharacterDie()
{
	
}

void APlayerCharacter::InitializePlayer()
{
#pragma region Asset
	// SkeletalMesh �ε�
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_BODY(
		TEXT("SkeletalMesh'/Game/Actors/PlayerCharacter/Mesh/ms06_Rat.ms06_Rat'"));
	// SkeletalMesh ����
	if (SK_BODY.Succeeded()) GetMesh()->SetSkeletalMesh(SK_BODY.Object);

	// ĳ���� �⺻ ��ġ / ȸ�� ����
	GetMesh()->SetRelativeLocationAndRotation(
		FVector::DownVector * 40.0f,
		FRotator(0.0f, -90.0f, 0.0f));

	GetCapsuleComponent()->SetCapsuleHalfHeight(40.0f);

	static ConstructorHelpers::FClassFinder<UPlayerAnimInst> ANIM_BP_PLAYER(
		TEXT("AnimBlueprint'/Game/Actors/PlayerCharacter/Animations/AnimBP_Player.AnimBP_Player_C'"));
	if (ANIM_BP_PLAYER.Succeeded()) GetMesh()->SetAnimClass(ANIM_BP_PLAYER.Class);
#pragma endregion

#pragma region Component
	MovementHelper = CreateDefaultSubobject<UMovementHelperComponent>(TEXT("MOVEMENT_HELPER"));
	ZoomableSpringArm = CreateDefaultSubobject<UZoomableSpringArmComponent>(TEXT("ZOOMABLE_SPRING_ARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	Camera->SetConstraintAspectRatio(false);

	// Spring Arm Component �� ��Ʈ ������Ʈ�� �߰��մϴ�.
	ZoomableSpringArm->SetupAttachment(GetRootComponent());

	// Camera Component �� SpringArm ������Ʈ�� �߰��մϴ�.
	Camera->SetupAttachment(ZoomableSpringArm);

	// ��Ʈ�ѷ��� ȸ������ SpringArm Component ȸ�������� ����մϴ�.
	ZoomableSpringArm->bUsePawnControlRotation = true;

	// ��Ʈ�ѷ��� ȸ���� Yaw, Pitch ȸ���� ����մϴ�.
	ZoomableSpringArm->bInheritYaw = true;
	ZoomableSpringArm->bInheritPitch = true;

	// SpringArm �������� �����մϴ�.
	ZoomableSpringArm->TargetOffset = FVector::UpVector * 40.0f;

	PlayerAttack = CreateDefaultSubobject<UPlayerAttackComponent>(TEXT("PLAYER_ATTACK_COM"));
#pragma endregion
}
