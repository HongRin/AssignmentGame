#include "Bullet.h"

ABullet::ABullet()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ST_STONE(
		TEXT("StaticMesh'/Game/Actors/Bullet/Meshes/SM_small_stone_02.SM_small_stone_02'"));
	if (ST_STONE.Succeeded()) BulletMeshAsset = ST_STONE.Object;
	else UE_LOG(LogTemp, Error, TEXT("ABullet.cpp::%d::LINE::ST_STONE is not loaded!"), __LINE__);

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CAPSULE_COM"));
	Capsule->SetCapsuleRadius(34.0f);
	Capsule->SetCapsuleHalfHeight(34.0f);
	
	if (IsValid(BulletMeshAsset))
	{
		BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ST_BULLET"));
		BulletMesh->SetStaticMesh(BulletMeshAsset);
		BulletMesh->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
		BulletMesh->SetRelativeLocation(FVector(0.0f, -30.0f, 0.0f));
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

}

void ABullet::OnRecycleStart()
{ }

