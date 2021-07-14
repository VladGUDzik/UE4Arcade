// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootComponent.h"
#include"Engine/World.h"
#include"TimerManager.h"

// Sets default values for this component's properties
UShootComponent::UShootComponent()
	:
	Shoot_Interval(1.f)
{

}


// Called when the game starts
void UShootComponent::BeginPlay()
{
	Super::BeginPlay();

	StartShotting();

}

void UShootComponent::Fire_Shoot()
{
	for (FShoot_inf Shoot_inf : Shoot_infs)
	{
		FActorSpawnParameters SpawnParameters;
		FVector SpawnLocation = GetOwner()->GetActorLocation();
		FRotator SpawnRotation;
		SpawnRotation.Add(0.f, Shoot_inf.Angle, 0.f);

		GetWorld()->SpawnActor<AProjectail>(Shoot_inf.Project_Class, SpawnLocation, SpawnRotation, SpawnParameters);
	}
}

void UShootComponent::StartShotting()
{
	GetWorld()->GetTimerManager().SetTimer(Shoot_in_the_Dark, this, &UShootComponent::Fire_Shoot, Shoot_Interval, true, 2.0f);
}

void UShootComponent::StopShotting()
{
	GetWorld()->GetTimerManager().ClearTimer(Shoot_in_the_Dark);
}


