#include"Ship.h"//���������� �������
#include"Components/StaticMeshComponent.h"//���������� UE4 ��� 3D-������ �������
#include "Particles/ParticleSystemComponent.h"//���������� ��� ����������(������ ���������)
#include"Components/InputComponent.h"//���������� ��� ������� ������
#include"GameFramework/Controller.h"
#include"GameFramework/Actor.h"//���������� �� ���������� ���������, ������� ����� ������� ������, ����� �������������� �� ��������. 
#include"Engine/World.h"//���������� ��� �������������� ������ GetWorld()
#include"TimerManager.h"//���������� ��� �������� �������
#include "Kismet/GameplayStatics.h"//���������� ��� ��������� ���������� � �����
#include "Sound/SoundBase.h"//���������� ��� ������������� �����

//��������� ����� � ����������� ������� � ������
const FName AShip::MoveForwardBinding("MoveForward");
const FName AShip::MoveRightBinding("MoveRight");
const FName AShip::FireBinding("Fire");
const FName AShip::AutoFireBinding("AutoFire");

AShip::AShip()
	:
	Shoot_Interval(0.5f)
{
	// �������� ������� Tick()
	PrimaryActorTick.bCanEverTick = true;

	//������� ����������,��� ������ ��������� ������:
	// 
	//������� ��������
	ShipCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("ShipCollision"));
	SetRootComponent(ShipCollision);
	ShipCollision->SetCollisionProfileName("Pawn");
	ShipCollision->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Ignore);

	//������� ������ �������
	ShipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	ShipMesh->SetupAttachment(ShipCollision);

	//������� ��������� ������
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true);//��������� ��� ��������� �������,��� ����� ������ �������� 
	CameraBoom->TargetArmLength = 1800.f;//����������
	CameraBoom->SetRelativeRotation(FRotator(-80.f, 0.f, 0.f));//������
	CameraBoom->bDoCollisionTest = false;

	//������� ������ ������
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(CameraBoom);
	CameraComponent->bUsePawnControlRotation = false;//��������� RelativeRotation ����������

	//������� ����� ���������
	ShipInputComponent = CreateDefaultSubobject<UInputComponent>(TEXT("ShipInputComponent"));
	//������� ��������� ���������
	ShootComponent = CreateDefaultSubobject<UShootComponent>(TEXT("ShootComponent"));

	//������ �������� �� ������� � ���������� �������
	ShipInputComponent->BindAction(FireBinding, IE_Pressed, this, &AShip::Start_Fire);
	ShipInputComponent->BindAction(FireBinding, IE_Released, this, &AShip::End_Fire); 
	ShipInputComponent->BindAction(AutoFireBinding, IE_Pressed, this, &AShip::Auto_Fire);
	
	
	//�������� �������
	MoveSpeed = 1000.0f;
}

void AShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	//�������� ������ �������
	PlayerInputComponent->BindAxis(MoveForwardBinding);
	PlayerInputComponent->BindAxis(MoveRightBinding);
	
}

void AShip::Start_Fire()
{
	if (FireSound != nullptr)//���� ����� ��� - �� �� ���������
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}
	ShootComponent->StartShotting();//���������� ������ ����������� ������
}

void AShip::End_Fire()
{
	ShootComponent->StopShotting();// ���������� ������ ����������� ������
}

void AShip::Auto_Fire()
{
	//������� ������ (������������� ���������)
	GetWorld()->GetTimerManager().SetTimer(Shoot_in_the_Dark, this, &AShip::Start_Fire, Shoot_Interval, true, 0.f);
}

void AShip::BeginPlay()
{
	//������ ����
	Super::BeginPlay();

	//��������� ������ � ��������
	GetWorld()->GetTimerManager().SetTimer(Shoot_in_the_Dark, this, &AShip::Start_Fire, Shoot_Interval, true, 0.f);
	ShipMaterial = ShipMesh->GetMaterial(0);
}

void AShip::DestroyShip_Implementation()
{
	//��������� ��������
	SetActorEnableCollision(false);

	//������� �����
	ShipInputComponent->ClearActionBindings();

	//������������� ��������
	ShootComponent->StopShotting();
	GetWorld()->GetTimerManager().ClearTimer(Shoot_in_the_Dark);//������� ������

	CameraShake(1.5f);//��������� ������ 

	ShipMesh->SetMaterial(0, RecoverMat);//�������� �������

	//��������� ��������, ���� ��� ����
	if (DestroyParticle)UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyParticle, GetActorTransform(), true);

	//���� ���������� ����������
	for (UActorComponent* Component : GetComponentsByClass(UParticleSystemComponent::StaticClass()))
	{
		Component->Deactivate();
	}

}

void AShip::RecoverShip_Implementation()
{
	//��������� ��������
	SetActorEnableCollision(true);
	//�������������� ������ ���������
	ShipInputComponent->BindAction(FireBinding, IE_Pressed, this, &AShip::Start_Fire);
	ShipInputComponent->BindAction(FireBinding, IE_Released, this, &AShip::End_Fire); 
	ShipInputComponent->BindAction(AutoFireBinding, IE_Pressed, this, &AShip::Auto_Fire);
	ShootComponent->StartShotting();
	//��������� �������
	GetWorld()->GetTimerManager().SetTimer(Shoot_in_the_Dark, this, &AShip::Auto_Fire, Shoot_Interval, true, 0.f);
	
	//��������� ��������� �������
	ShipMesh->SetMaterial(0, ShipMaterial);
	//���� ����������
	for (UActorComponent* Component : GetComponentsByClass(UParticleSystemComponent::StaticClass()))
	{
		Component->Activate(true);
	}
}

float AShip::TakeDamage(float Damage, const FDamageEvent& DamageEvent, AController* Instigat, AActor* DamageCauser)
{
	//���� �� �������� ������� ���� ��������� 0.f
	if (!CanBeDamaged())return 0.f;
	if (DestoySound != nullptr)//���� ���� ���� - �� �����������
	{
		UGameplayStatics::PlaySoundAtLocation(this, DestoySound, GetActorLocation());
	}
	//��������� ���������� ����
	Super::TakeDamage(Damage, DamageEvent, Instigat, DamageCauser);
	PawnDamage.Broadcast();
	return Damage;
}

void AShip::CameraShake(float Scale)
{
	if(CamShake!=NULL)
	GetWorld()->GetFirstPlayerController()->PlayerCameraManager->PlayCameraShake(CamShake, Scale);
}

bool AShip::CanBeDamaged_Implementation()
{
	//�������� �� ������ ����
	return bCanBeDamaged;
	
}

void AShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//������������ ����������� ������-����� � ������-����� 
	const float ForwardValue = GetInputAxisValue(MoveForwardBinding);
	const float RightValue = GetInputAxisValue(MoveRightBinding);

	//�������� �������� �����������
	const FVector MoveDirection = FVector(ForwardValue, RightValue, 0.f).GetClampedToMaxSize(1.0f);
	//������� ��������
	const FVector Movement = MoveDirection * MoveSpeed * DeltaTime;

	//���� �������� ���������
	if (Movement.SizeSquared() > 0.0f)
	{
		//�������� �������� ������������
		FVector NewLocation = GetActorLocation();
		//������� ��� ������ �� XY
		NewLocation.X = FMath::Clamp(NewLocation.X + MoveDirection.Y, -1050.f, 1250.f);
		NewLocation.Y = FMath::Clamp(NewLocation.Y + MoveDirection.X, -1700.f, 1700.f);
		//������������� �������
		SetActorLocation(NewLocation);
		//������� �������� ���������
		const FRotator NewRotation = Movement.Rotation();
		FHitResult Hit(1.f);
		//������������� ���������� � ��������� ������
		RootComponent->MoveComponent(Movement, NewRotation, true, &Hit);
		if (Hit.IsValidBlockingHit())//�������� 2D �����������
		{
			const FVector Normal2D = Hit.Normal.GetSafeNormal2D();
			const FVector Deflection = FVector::VectorPlaneProject(Movement, Normal2D) * (1.f - Hit.Time);
			RootComponent->MoveComponent(Deflection, NewRotation, true);
		}
	}
}
