// Fill out your copyright notice in the Description page of Project Settings.
#include "Ship.h"
#include "Projectail.h"
#include"Components/StaticMeshComponent.h"
#include"Components/InputComponent.h"
#include"GameFramework/Controller.h"

const FName AShip::MoveForwardBinding("MoveForward");
const FName AShip::MoveRightBinding("MoveRight");
const FName AShip::FireBinding("Fire");


// Sets default values
AShip::AShip()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ShipCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("ShipCollision"));
	SetRootComponent(ShipCollision);

	ShipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	ShipMesh->SetupAttachment(ShipCollision);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);

	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-80.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = sasdwfalse;

	CameraComponent = CreateAbstractDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(CameraBoom);
	CameraComponent->bUsePawnControlRotation = false;

	ShootComponent = CreateDefaultSubobject<UShootComponent>(TEXT("ShootComponent"));

	MoveSpeed = 1000.0f;

	bCanFire = false;
}

// Called to bind functionality to input
void AShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis(MoveForwardBinding);
	PlayerInputComponent->BindAxis(MoveRightBinding);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AShip::Fire_Time);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AShip::End_Fire_Time);

}

// Called every frame
void AShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const float ForwardValue = GetInputAxisValue(MoveForwardBinding);
	const float RightValue = GetInputAxisValue(MoveRightBinding);

	const FVector MoveDirection = FVector(ForwardValue, RightValue, 0.f).GetClampedToMaxSize(1.0f);
	const FVector Movement = MoveDirection * MoveSpeed * DeltaTime;

	if (Movement.SizeSquared() > 0.0f)
	{
		const FRotator NewRotation = Movement.Rotation();
		FHitResult Hit(1.f);
		RootComponent->MoveComponent(Movement, NewRotation, true, &Hit);
		if (Hit.IsValidBlockingHit())
		{
			const FVector Normal2D = Hit.Normal.GetSafeNormal2D();
			const FVector Deflection = FVector::VectorPlaneProject(Movement, Normal2D) * (1.f - Hit.Time);
			RootComponent->MoveComponent(Deflection, NewRotation, true);
		}
		if (bCanFire)
		{
			ShootComponent->StartShotting();
		}
		else
		{
			ShootComponent->StopShotting();
		}
	}

}

void AShip::Fire_Time()
{
	bCanFire = true;
}

void AShip::End_Fire_Time()
{
	bCanFire = false;
}






