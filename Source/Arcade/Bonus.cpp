#include "Bonus.h"
#include"Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Arcade/Ship.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"


ABonus::ABonus()
{
	PrimaryActorTick.bCanEverTick = true;
	Collis = CreateDefaultSubobject<USphereComponent>(TEXT("Collis"));
	SetRootComponent(Collis);
	Collis->SetCollisionObjectType(ECC_WorldDynamic);
	//������ �����
	Collis->SetSphereRadius(50.f);
}

void ABonus::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (!OtherActor)return;//���� ����� ���������� 
	if (!Cast<AShip>(OtherActor))return;

	if (CollectedSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, CollectedSound, GetActorLocation());
	}
	BonusCollect();

}

void ABonus::BonusCollect_Implementation()
{
	//������ ������ �������
	if (CollectParticle)UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), CollectParticle, GetActorTransform(), true);

	Destroy();
}

void ABonus::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//���������� �������
	float WorldMoveOffSet = -300.f * DeltaTime;
	AddActorLocalOffset(FVector( WorldMoveOffSet,0.f, 0.f));
}
