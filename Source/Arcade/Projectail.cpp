// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectail.h"
#include"Components/StaticMeshComponent.h"

// Sets default values
AProjectail::AProjectail()
	:
	Projectil_Speed(120.f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Project_Collis = CreateDefaultSubobject<USphereComponent>(TEXT("Project_Collis"));
	SetRootComponent(Project_Collis);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Project_Collis);
	Project_Move= CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Project_Move"));
	Mesh->SetCollisionProfileName("NoCollision");

	Project_Move->InitialSpeed = 4000.f;
	Project_Move->MaxSpeed = 4500.f;

	Project_Move->ProjectileGravityScale = 0.f;
	InitialLifeSpan = 3.0f;
}

// Called when the game starts or when spawned
void AProjectail::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectail::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalOffset(FVector(Projectil_Speed * DeltaTime, 0.f, 0.f));
}

