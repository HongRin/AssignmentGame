#include "Bullet.h"
#include "Actors/Characters/PlayerCharacter/PlayerCharacter.h"
#include "Actors/Controllers/PlayerController/PlayableController.h"
#include "Actors/Characters/MonsterCharacter/MonsterCharacter.h"
#include "Single/GameInstance/AGGameInst.h"
#include "Single/PlayerManager/PlayerManager.h"

ABullet::ABullet()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ST_STONE(
		TEXT("StaticMesh'/Game/Actors/Bullet/Meshes/SM_small_stone_02.SM_small_stone_02'"));
	if (ST_STONE.Succeeded()) BulletMeshAsset = ST_STONE.Object;
	else UE_LOG(LogTemp, Error, TEXT("ABullet.cpp::%d::LINE::ST_STONE is not loaded!"), __LINE__);

	if (IsValid(BulletMeshAsset))
	{
		BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ST_BULLET"));
		BulletMesh->SetupAttachment(GetRootComponent());
		BulletMesh->SetStaticMesh(BulletMeshAsset);
		BulletMesh->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
	}

	BulletSphere = CreateDefaultSubobject<USphereComponent>(TEXT("BULLET_SPHERE"));
	BulletSphere->SetupAttachment(BulletMesh);
	BulletSphere->SetSphereRadius(40.0f);

	SetID(DEFAULT_BULLET);
}

void ABullet::BeginPlay()
{
	Super::BeginPlay();

	BulletSphere->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnMonsterHit);
}

void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Fire();
}

void ABullet::InitializeBullet(FVector loc, FRotator roc, FVector fireDirection, FVector fireLocation)
{
	SetActorLocationAndRotation(loc, roc);
	FireDirection = fireDirection;
	FireLocation = fireLocation;
}

void ABullet::Fire()
{
	float firingdistance = FVector::Distance(GetActorLocation(), FireLocation);

	if (firingdistance > 600.0f)
	{
		SetCanRecyclable(true);
		BulletMesh->SetHiddenInGame(true);
		return;
	}
	SetActorLocation(GetActorLocation() + FireDirection * 15.0f, true);

}

void ABullet::OnMonsterHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag(TEXT("Monster")))
	{
		if (OtherComp == Cast<AMonsterCharacter>(OtherActor)->GetCapsuleComponent())
		{
			OtherActor->TakeDamage(
				GetManager(UPlayerManager)->GetPlayerInfo()->Atk,
				FDamageEvent(),
				GetManager(UPlayerManager)->GetPlayableController(),
				GetManager(UPlayerManager)->GetPlayableCharacter());

			SetCanRecyclable(true);
			BulletMesh->SetHiddenInGame(true);
		}
	}
}

void ABullet::OnRecycleStart()
{
	BulletMesh->SetHiddenInGame(false);
}

