#include "PlayerDetectorComponent.h"

UPlayerDetectorComponent::UPlayerDetectorComponent()
{
	SphereRadius = 200.0f;
	SetHiddenInGame(false);
}

void UPlayerDetectorComponent::BeginPlay()
{
	Super::BeginPlay();

	OnComponentBeginOverlap.AddDynamic(this, &UPlayerDetectorComponent::OnPlayerDetected);
	OnComponentEndOverlap.AddDynamic(this, &UPlayerDetectorComponent::OnPlayerLost);
}

void UPlayerDetectorComponent::OnPlayerDetected(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag(TEXT("Player")))
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerCharacter Detected!"));
		bDetectPlayer = true;
	}
}

void UPlayerDetectorComponent::OnPlayerLost(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->ActorHasTag(TEXT("Player")))
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerCharacter Lost!"));
		bDetectPlayer = false;
	}
}
