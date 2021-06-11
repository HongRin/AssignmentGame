#include "MonsterCharacter.h"
#include "Actors/Controllers/MonsterController/MonsterController.h"
#include "AnimInstance/MonsterAnimInst/MonsterAnimInst.h"

#include "Components/MonsterAttack/MonsterAttackComponent.h"
#include "Components/PlayerDetector/PlayerDetectorComponent.h"

#include "Single/GameInstance/AGGameInst.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "BrainComponent.h"

AMonsterCharacter::AMonsterCharacter()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_MONSTER_INFO(
		TEXT("DataTable'/Game/DataTable/DT_MonsterInfo.DT_MonsterInfo'"));
	if (DT_MONSTER_INFO.Succeeded()) DT_MonsterInfo = DT_MONSTER_INFO.Object;

	// ���������� �����մϴ�.
	SetGenericTeamId(TEAM_MONSTER);

	AIControllerClass = AMonsterController::StaticClass();

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("MonsterCollision"));
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));

	PlayerDetector = CreateDefaultSubobject<UPlayerDetectorComponent>(TEXT("PLAYER_DETECTOR"));
	PlayerDetector->SetupAttachment(GetRootComponent());

	MonsterAttack = CreateDefaultSubobject<UMonsterAttackComponent>(TEXT("MONSTER_ATTACK"));
}

void AMonsterCharacter::BeginPlay()
{
	Super::BeginPlay();

	GameInst = GetGameInst(this);

	// ���� ���� ����
	InitializeMonsterDataConstructTime();

	Tags.Add(TEXT("Monster"));
}

void AMonsterCharacter::OnTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	Super::OnTakeDamage(DamagedActor, Damage, DamageType, InstigatedBy, DamageCauser);

	UE_LOG(LogTemp, Warning, TEXT("Name[%s]::MaxHp[%.1f]::Hp[%.1f]"), 
		*MonsterInfo.MonsterName.ToString(), GetMaxHp(), GetHp());
}

void AMonsterCharacter::InitializeSkeletalMeshComponent()
{
	// ���� SkeletalMesh �񵿱� �ε�
	auto monsterMesh = Cast<USkeletalMesh>(
		GetManager(FStreamableManager)->LoadSynchronous(MonsterInfo.SkeletalMeshPath));

	// �ִ� �������Ʈ Asset �񵿱� �ε�
	UBlueprint* monsterAnimInstClass = Cast<UBlueprint>(
		GetManager(FStreamableManager)->LoadSynchronous(MonsterInfo.AnimInstanceClassPath));

	if (IsValid(monsterMesh))
	{
		// SkeletalMesh ����
		GetMesh()->SetSkeletalMesh(monsterMesh);

		// ��ġ ȸ�� ����
		GetMesh()->SetRelativeLocationAndRotation(
			FVector(0.0f, 0.0f, -(GetCapsuleComponent()->GetScaledCapsuleHalfHeight())),
			FRotator(0.0f, -90.0f, 0.0f));
	}
	else
		UE_LOG(LogTemp, Error, TEXT("AMonsterCharacter.cpp :: %d LINE :: monstermesh is not loaded!"), __LINE__);

	if (IsValid(monsterAnimInstClass))
	{
		// �ִ��ν��ͽ� ��ȯ
		TSubclassOf<UMonsterAnimInst> bpAnimInstClass =
			static_cast<TSubclassOf<UMonsterAnimInst>>(monsterAnimInstClass->GeneratedClass);

		// �ִ� Ŭ���� ����
		GetMesh()->SetAnimClass(bpAnimInstClass);
	}
	else 
		UE_LOG(LogTemp, Error, TEXT("AMonsterCharacter.cpp :: %d LINE :: monsterAnimInstClass is not loaded!"), __LINE__);
}

void AMonsterCharacter::InitializeMonsterDataConstructTime()
{
	// ���� �ڵ�� ���� ������ ������
	FString contextString;
	FMonsterInfo* monsterInfo = DT_MonsterInfo->FindRow<FMonsterInfo>(
		MonsterCode, contextString);

	if (monsterInfo == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AMonsterCharacter.cpp :: %d LINE :: monsterInfo is not loaded!"), __LINE__);
		return;
	}

	// ���� ���� ����
	MonsterInfo = (*monsterInfo);

	// Hp ����
	Hp = MaxHp = monsterInfo->MaxHp;

	// Atk ����
	Atk = monsterInfo->Atk;

	// �ӷ� ����
	GetCharacterMovement()->MaxWalkSpeed = MonsterInfo.MoveSpeed;

	// SkeletalMesh �ʱ�ȭ
	InitializeSkeletalMeshComponent();
}

void AMonsterCharacter::OnCharacterDie()
{
}
