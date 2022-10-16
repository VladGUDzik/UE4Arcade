
#include "ShootComponent.h"
#include"Engine/World.h"
#include"TimerManager.h"
#include "Engine/StaticMesh.h"//StaticMesh — это часть геометрии, состоящая из статического набора полигонов

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
	for (FShoot_inf Shoot_inf : Shoot_infs)//массив из структур выстрелов
	{
		FActorSpawnParameters SpawnParameters;//спаун параметр
		SpawnParameters.Owner=GetOwner();
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		//получаем локацию спаунов : прибавляем место расположения выстрела к месту расположения спауна
		FVector SpawnLocation =
			GetOwner()->GetActorLocation()
			+
			GetOwner()->GetActorRotation().RotateVector(Shoot_inf.GunOffset);
		FRotator SpawnRotation=GetOwner()->GetActorRotation();
		//устанавливаем угол наклона вычтрела
		SpawnRotation.Add(0.f, Shoot_inf.Angle, 0.f);

		//присваиваем урон единичному выстрелу
		AProjectail* Projectail =GetWorld()->SpawnActor<AProjectail>(Shoot_inf.Project_Class, SpawnLocation, SpawnRotation, SpawnParameters);
		if (Projectail)Projectail->Damage = Shoot_inf.Damage;

	}
}

void UShootComponent::StartShotting()
{
	//зацикленнный таймер стрельбы
	GetWorld()->GetTimerManager().SetTimer(Shoot_in_the_Dark, this, &UShootComponent::Fire_Shoot, Shoot_Interval, true, 0.f);
}

void UShootComponent::StopShotting()
{
	//очищенный таймер
	GetWorld()->GetTimerManager().ClearTimer(Shoot_in_the_Dark);
}


