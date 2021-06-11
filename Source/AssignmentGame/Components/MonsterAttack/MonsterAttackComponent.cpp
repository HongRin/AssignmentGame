#include "MonsterAttackComponent.h"
#include "Actors/Characters/MonsterCharacter/MonsterCharacter.h"
#include "Structures/MonsterInfo/MonsterInfo.h"


UMonsterAttackComponent::UMonsterAttackComponent()
{
	MonsterCharacter = Cast<AMonsterCharacter>(GetOwner());

	AttackState = false;
}

void UMonsterAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	MonsterCharacter = Cast<AMonsterCharacter>(GetOwner());

	OnMonsterAttackFinished.AddLambda([this]()->void { AttackState = false; });
}

void UMonsterAttackComponent::PlayMonsterAttackAnimation()
{
	if (AttackState) return;
	if (!IsValid(MonsterAttack)) return;

	UE_LOG(LogTemp, Warning, TEXT("MonsterAttackAnim"));

	if (FMath::FRandRange(0, 100) < 50.0f)
		MonsterCharacter->PlayAnimMontage(MonsterAttack, 1.0f, TEXT("AttackOne"));
	else
		MonsterCharacter->PlayAnimMontage(MonsterAttack, 1.0f, TEXT("AttackTwo"));

	AttackState = true;
}

void UMonsterAttackComponent::ActiveMonsterAttackRange()
{
	TArray<AActor*> actorsToIgnore;
	actorsToIgnore.Add(MonsterCharacter);

	TArray<FHitResult> outHits;

	UKismetSystemLibrary::SphereTraceMultiByProfile(
		GetWorld(),
		MonsterCharacter->GetActorLocation(),
		MonsterCharacter->GetActorLocation() + (MonsterCharacter->GetActorForwardVector() * 200.0f),
		200.0f,
		TEXT("AttackRange"),
		true,
		actorsToIgnore,
		EDrawDebugTrace::Type::ForDuration,
		outHits,
		true,
		FLinearColor::Red,
		FLinearColor::Red,
		2.0f
	);

	for (auto hit : outHits)
	{
		if (!hit.GetActor()->ActorHasTag(TEXT("Monster")))
		{
			hit.GetActor()->TakeDamage(
				MonsterCharacter->GetAtk(),
				FDamageEvent(),
				MonsterCharacter->GetController(),
				MonsterCharacter);
		}
	}
}

