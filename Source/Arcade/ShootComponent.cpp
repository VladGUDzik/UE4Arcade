
#include "ShootComponent.h"
#include"Engine/World.h"
#include"TimerManager.h"
#include "Engine/StaticMesh.h"//StaticMesh � ��� ����� ���������, ��������� �� ������������ ������ ���������

UShootComponent::UShootComponent()
	:
	Shoot_Interval(0.5f)
{
}

void UShootComponent::BeginPlay()
{
	Super::BeginPlay();
	//StartShotting();
}

void UShootComponent::Fire_Shoot()
{
	for (FShoot_inf Shoot_inf : Shoot_infs)//������ �� �������� ���������
	{
		FActorSpawnParameters SpawnParameters;//����� ��������
		SpawnParameters.Owner=GetOwner();
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		//�������� ������� ������� : ���������� ����� ������������ �������� � ����� ������������ ������
		FVector SpawnLocation =
			GetOwner()->GetActorLocation()
			+
			GetOwner()->GetActorRotation().RotateVector(Shoot_inf.GunOffset);
		FRotator SpawnRotation=GetOwner()->GetActorRotation();
		//������������� ���� ������� ��������
		SpawnRotation.Add(0.f, Shoot_inf.Angle, 0.f);

		//����������� ���� ���������� ��������
		AProjectail* Projectail =GetWorld()->SpawnActor<AProjectail>(Shoot_inf.Project_Class, SpawnLocation, SpawnRotation, SpawnParameters);
		if (Projectail)Projectail->Damage = Shoot_inf.Damage;

	}
}

void UShootComponent::StartShotting()
{
	//������������ ������ ��������
	GetWorld()->GetTimerManager().SetTimer(Shoot_in_the_Dark, this, &UShootComponent::Fire_Shoot, Shoot_Interval, true, 0.f);
}

void UShootComponent::StopShotting()
{
	//��������� ������
	GetWorld()->GetTimerManager().ClearTimer(Shoot_in_the_Dark);
}


