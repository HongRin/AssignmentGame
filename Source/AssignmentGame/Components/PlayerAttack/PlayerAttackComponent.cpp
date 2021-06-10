#include "PlayerAttackComponent.h"
#include "Actors/Characters/PlayerCharacter/PlayerCharacter.h"
#include "Actors/PoolableActor/Bullet/Bullet.h"
#include "Components/MovementHelper/MovementHelperComponent.h"
#include "Util/ObjectPool.h"

UPlayerAttackComponent::UPlayerAttackComponent()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AM_ATTACK(
		TEXT("AnimMontage'/Game/Actors/PlayerCharacter/Animations/AM_Attack.AM_Attack'"));
	if (AM_ATTACK.Succeeded()) AttackAnimMontage = AM_ATTACK.Object;

	static ConstructorHelpers::FClassFinder<ABullet> BP_BULLET(
		TEXT("Blueprint'/Game/Blueprints/Actors/Test/BP_Bullet.BP_Bullet_C'"));
	if (BP_BULLET.Succeeded()) BP_Bullet = BP_BULLET.Class;
	else UE_LOG(LogTemp, Error, TEXT("UPlayerAttackComponent.cpp::%d::LINE::BP_BULLET is not loaded!"), __LINE__);
}

void UPlayerAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	BulletObjectPool = NewObject<UObjectPool>();


	PlayerCharacter = Cast<APlayerCharacter>(GetOwner());

	OnAttackFinished.AddLambda([this]()->void {
		IsAttack = false;
		PlayerCharacter->GetMovementHelper()->SetIsCanMove(true);
		});
}

void UPlayerAttackComponent::PlayAttack()
{
	if (IsAttack) return;
	IsAttack = true;
	PlayerCharacter->GetMovementHelper()->SetIsCanMove(false);
	PlayerCharacter->PlayAnimMontage(AttackAnimMontage);
}

void UPlayerAttackComponent::CreateBullet()
{
	auto bullet = Cast<ABullet>(
		BulletObjectPool->GetRecycledObject(DEFAULT_BULLET));

	if (!IsValid(bullet))
	{
		BulletObjectPool->RegisterRecyclableObject(
			bullet = GetWorld()->SpawnActor<ABullet>(BP_Bullet));
	}

	bullet->InitializeBullet(PlayerCharacter->GetActorLocation() + PlayerCharacter->GetActorForwardVector() * 40.0f);
}

