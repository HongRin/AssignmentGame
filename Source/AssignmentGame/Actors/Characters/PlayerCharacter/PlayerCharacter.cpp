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

	// 플레이어 팀으로 설정합니다.
	SetGenericTeamId(TEAM_PLAYER);

	// 이 액터의 회전이 컨트롤러의 Yaw 회전을 사용하지 않도록 합니다.
	bUseControllerRotationYaw = false;

	// 이동하는 방향으로 캐릭터를 회전시킵니다.
	GetCharacterMovement()->bOrientRotationToMovement = true;

	// 회전 속도를 지정합니다.
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
	// SkeletalMesh 로드
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_BODY(
		TEXT("SkeletalMesh'/Game/Actors/PlayerCharacter/Mesh/ms06_Rat.ms06_Rat'"));
	// SkeletalMesh 설정
	if (SK_BODY.Succeeded()) GetMesh()->SetSkeletalMesh(SK_BODY.Object);

	// 캐릭터 기본 위치 / 회전 설정
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

	// Spring Arm Component 를 루트 컴포넌트에 추가합니다.
	ZoomableSpringArm->SetupAttachment(GetRootComponent());

	// Camera Component 를 SpringArm 컴포넌트에 추가합니다.
	Camera->SetupAttachment(ZoomableSpringArm);

	// 컨트롤러의 회전값을 SpringArm Component 회전값으로 사용합니다.
	ZoomableSpringArm->bUsePawnControlRotation = true;

	// 컨트롤러의 회전중 Yaw, Pitch 회전을 사용합니다.
	ZoomableSpringArm->bInheritYaw = true;
	ZoomableSpringArm->bInheritPitch = true;

	// SpringArm 오프셋을 설정합니다.
	ZoomableSpringArm->TargetOffset = FVector::UpVector * 40.0f;

	PlayerAttack = CreateDefaultSubobject<UPlayerAttackComponent>(TEXT("PLAYER_ATTACK_COM"));
#pragma endregion
}
