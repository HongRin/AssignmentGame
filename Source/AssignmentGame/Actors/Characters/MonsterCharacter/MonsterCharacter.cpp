#include "MonsterCharacter.h"
#include "Actors/Characters/PlayerCharacter/PlayerCharacter.h"
#include "Actors/Controllers/MonsterController/MonsterController.h"
#include "AnimInstance/MonsterAnimInst/MonsterAnimInst.h"

#include "Components/MonsterAttack/MonsterAttackComponent.h"
#include "Components/PlayerDetector/PlayerDetectorComponent.h"
#include "Components/MonsterWidget/MonsterWigdetComponent.h"

#include "Level/DungeonLevel.h"

#include "Widgets/CharacterWidget/Monster/HpableCharacterWidget.h"
#include "Widgets/CharacterWidget/Player/PlayerWidget.h"

#include "Single/GameInstance/AGGameInst.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "BrainComponent.h"

AMonsterCharacter::AMonsterCharacter()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_MONSTER_INFO(
		TEXT("DataTable'/Game/DataTable/DT_MonsterInfo.DT_MonsterInfo'"));
	if (DT_MONSTER_INFO.Succeeded()) DT_MonsterInfo = DT_MONSTER_INFO.Object;

	// 몬스터팀으로 설정합니다.
	SetGenericTeamId(TEAM_MONSTER);

	AIControllerClass = AMonsterController::StaticClass();

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("MonsterCollision"));
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));

	PlayerDetector = CreateDefaultSubobject<UPlayerDetectorComponent>(TEXT("PLAYER_DETECTOR"));
	PlayerDetector->SetupAttachment(GetRootComponent());

	MonsterAttack = CreateDefaultSubobject<UMonsterAttackComponent>(TEXT("MONSTER_ATTACK"));

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("MonsterCollision"));
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));

	MonsterWidget = CreateDefaultSubobject<UMonsterWigdetComponent>(TEXT("Monster_WIDGET"));
	MonsterWidget->SetupAttachment(GetRootComponent());
}

void AMonsterCharacter::BeginPlay()
{
	Super::BeginPlay();

	GameInst = GetGameInst(this);

	// 몬스터 정보 설정
	InitializeMonsterDataConstructTime();

	Tags.Add(TEXT("Monster"));

	// 위젯 셋팅
	MonsterWidget->GetMonsterWidgetInstance()->InitializeWidget(this);
	MonsterWidget->GetMonsterWidgetInstance()->SetNameText(MonsterInfo.MonsterName);
	MonsterWidget->GetMonsterWidgetInstance()->SetLevelText(0);
	MonsterWidget->GetMonsterWidgetInstance()->UpdateHp();

	DungeonLevel = Cast<ADungeonLevel>(GetWorld()->GetLevelScriptActor());
	DungeonLevel->AddMonsterCharacters(this);
}

void AMonsterCharacter::OnTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	Super::OnTakeDamage(DamagedActor, Damage, DamageType, InstigatedBy, DamageCauser);

	MonsterWidget->GetMonsterWidgetInstance()->UpdateHp();
}

void AMonsterCharacter::InitializeSkeletalMeshComponent()
{
	// 몬스터 SkeletalMesh 비동기 로드
	auto monsterMesh = Cast<USkeletalMesh>(
		GetManager(FStreamableManager)->LoadSynchronous(MonsterInfo.SkeletalMeshPath));

	// 애님 블루프린트 Asset 비동기 로드
	UBlueprint* monsterAnimInstClass = Cast<UBlueprint>(
		GetManager(FStreamableManager)->LoadSynchronous(MonsterInfo.AnimInstanceClassPath));

	if (IsValid(monsterMesh))
	{
		// SkeletalMesh 설정
		GetMesh()->SetSkeletalMesh(monsterMesh);

		// 위치 회전 설정
		GetMesh()->SetRelativeLocationAndRotation(
			FVector(0.0f, 0.0f, -(GetCapsuleComponent()->GetScaledCapsuleHalfHeight())),
			FRotator(0.0f, -90.0f, 0.0f));
	}
	else
		UE_LOG(LogTemp, Error, TEXT("AMonsterCharacter.cpp :: %d LINE :: monstermesh is not loaded!"), __LINE__);

	if (IsValid(monsterAnimInstClass))
	{
		// 애님인스터스 변환
		TSubclassOf<UMonsterAnimInst> bpAnimInstClass =
			static_cast<TSubclassOf<UMonsterAnimInst>>(monsterAnimInstClass->GeneratedClass);

		// 애님 클래스 설정
		GetMesh()->SetAnimClass(bpAnimInstClass);
	}
	else 
		UE_LOG(LogTemp, Error, TEXT("AMonsterCharacter.cpp :: %d LINE :: monsterAnimInstClass is not loaded!"), __LINE__);
}

void AMonsterCharacter::InitializeMonsterDataConstructTime()
{
	// 몬스터 코드와 같은 정보를 가져옴
	FString contextString;
	FMonsterInfo* monsterInfo = DT_MonsterInfo->FindRow<FMonsterInfo>(
		MonsterCode, contextString);

	if (monsterInfo == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AMonsterCharacter.cpp :: %d LINE :: monsterInfo is not loaded!"), __LINE__);
		return;
	}

	// 몬스터 정보 저장
	MonsterInfo = (*monsterInfo);

	// Hp 설정
	Hp = MaxHp = monsterInfo->MaxHp;

	// Atk 설정
	Atk = monsterInfo->Atk;

	// 속력 설정
	GetCharacterMovement()->MaxWalkSpeed = MonsterInfo.MoveSpeed;

	// SkeletalMesh 초기화
	InitializeSkeletalMeshComponent();
}

bool AMonsterCharacter::IsMovable() const
{
	return !GetMonsterAttack()->IsMonsterAttacking();
}

void AMonsterCharacter::OnCharacterDie()
{
	Super::OnCharacterDie();

	GetManager(UPlayerManager)->GetPlayerInfo()->Money += MonsterInfo.DropMoney;
	GetManager(UPlayerManager)->GetPlayableCharacter()->GetPlayerWidget()->UpdateMoney();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	FString reason;
	Cast<AMonsterController>(GetController())->GetBrainComponent()->StopLogic(reason);
	DungeonLevel->RemoveMonsterCharacters(this);

	if (DungeonLevel->DungeonClear())
		GetManager(UPlayerManager)->GetPlayableCharacter()->GetPlayerWidget()->PlayGameStateAnimation(true);

	Destroy();
}
