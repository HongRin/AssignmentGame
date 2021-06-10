#include "Bullet.h"
#include "Actors/Characters/PlayerCharacter/PlayerCharacter.h"

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

	SetID(DEFAULT_BULLET);
}

void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Fire();
}

void ABullet::InitializeBullet(FVector loc, FRotator roc, FVector fireDirection)
{
	SetActorLocationAndRotation(loc, roc);
	FireDirection = fireDirection;
}

void ABullet::Fire()
{
	SetActorLocation(GetActorLocation() + FireDirection * 15.0f);
}

void ABullet::OnRecycleStart()
{ }

