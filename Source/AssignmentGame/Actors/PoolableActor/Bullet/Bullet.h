#pragma once

#include "AssignmentGame.h"
#include "GameFramework/Actor.h"
#include "Interfaces/ObjectPoolable.h"
#include "Bullet.generated.h"

UCLASS()
class ASSIGNMENTGAME_API ABullet : public AActor,
	public IObjectPoolable
{
	GENERATED_BODY()

private :
	class UStaticMesh* BulletMeshAsset;
	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default", meta = (AllowPrivateAccess = true))
	class UStaticMeshComponent* BulletMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default", meta = (AllowPrivateAccess = true))
	class USphereComponent* BulletSphere;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 Id;

	UPROPERTY()
	bool bCanRecyclable;

	UPROPERTY()
	FVector FireDirection;

	UPROPERTY()
	FVector FireLocation;

public:	
	ABullet();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public :
	void InitializeBullet(FVector loc, FRotator roc, FVector fireDirection, FVector fireLocation);

private:
	void Fire();

private:
	UFUNCTION()
		void OnMonsterHit(
			UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

public:
	FORCEINLINE virtual int32 GetID() const override
	{ return Id; }

	FORCEINLINE virtual void SetID(int32 id)
	{ Id = id; }

	// ���� ���� ���θ� ��Ÿ���� ������ ���� ������ / ������
	FORCEINLINE virtual bool GetCanRecyclable() const override
	{ return bCanRecyclable; }

	FORCEINLINE virtual void SetCanRecyclable(bool canRecyclable) override
	{ bCanRecyclable = canRecyclable; }

	// ��Ȱ���� �Ǵ� �������� ȣ��Ǵ� �޼���
	virtual void OnRecycleStart() override;
};
