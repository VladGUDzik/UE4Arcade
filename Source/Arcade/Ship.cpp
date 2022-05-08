#include"Ship.h"//библиотека корабля
#include"Components/StaticMeshComponent.h"//библиотека UE4 для 3D-модели корабля
#include "Particles/ParticleSystemComponent.h"//библиотека для партиколов(частиц двигателя)
#include"Components/InputComponent.h"//библиотека для инпутов игрока
#include"GameFramework/Controller.h"
#include"GameFramework/Actor.h"//библиотека не физических субьектов, которые могут владеть пешкой, чтобы контролировать ее действия. 
#include"Engine/World.h"//библиотека для задействования фунции GetWorld()
#include"TimerManager.h"//библиотека для создания таймера
#include "Kismet/GameplayStatics.h"//библиотека для проигрыша партиколов и звука
#include "Sound/SoundBase.h"//библиотека для использованяи звука

//связываем бинды с настройками клавишь в движке
const FName AShip::MoveForwardBinding("MoveForward");
const FName AShip::MoveRightBinding("MoveRight");
const FName AShip::FireBinding("Fire");
const FName AShip::AutoFireBinding("AutoFire");

AShip::AShip()
	:
	Shoot_Interval(0.5f)
{
	// включаем функцию Tick()
	PrimaryActorTick.bCanEverTick = true;

	//создаем переменные,что хранят фунционал класса:
	// 
	//создаем каллизию
	ShipCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("ShipCollision"));
	SetRootComponent(ShipCollision);
	ShipCollision->SetCollisionProfileName("Pawn");
	ShipCollision->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Ignore);

	//создаем модель корабля
	ShipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	ShipMesh->SetupAttachment(ShipCollision);

	//создаем крепление камеры
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true);//отключаем все возможные эффекты,что могут камере помешать 
	CameraBoom->TargetArmLength = 1800.f;//расстояние
	CameraBoom->SetRelativeRotation(FRotator(-80.f, 0.f, 0.f));//наклон
	CameraBoom->bDoCollisionTest = false;

	//создаем камеру игрока
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(CameraBoom);
	CameraComponent->bUsePawnControlRotation = false;//сохраняем RelativeRotation компонента

	//создаем инпут копмонент
	ShipInputComponent = CreateDefaultSubobject<UInputComponent>(TEXT("ShipInputComponent"));
	//создаем компонент выстрелов
	ShootComponent = CreateDefaultSubobject<UShootComponent>(TEXT("ShootComponent"));

	//задаем действие на нажатие и отпускание клавиши
	ShipInputComponent->BindAction(FireBinding, IE_Pressed, this, &AShip::Start_Fire);
	ShipInputComponent->BindAction(FireBinding, IE_Released, this, &AShip::End_Fire); 
	ShipInputComponent->BindAction(AutoFireBinding, IE_Pressed, this, &AShip::Auto_Fire);
	
	
	//скорость корабля
	MoveSpeed = 1000.0f;
}

void AShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	//движение самого корабля
	PlayerInputComponent->BindAxis(MoveForwardBinding);
	PlayerInputComponent->BindAxis(MoveRightBinding);
	
}

void AShip::Start_Fire()
{
	if (FireSound != nullptr)//если звука нет - он не включится
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}
	ShootComponent->StartShotting();//используем фунцию самописного класса
}

void AShip::End_Fire()
{
	ShootComponent->StopShotting();// используем фунцию самописного класса
}

void AShip::Auto_Fire()
{
	//создаем таймер (переодичность выстрелов)
	GetWorld()->GetTimerManager().SetTimer(Shoot_in_the_Dark, this, &AShip::Start_Fire, Shoot_Interval, true, 0.f);
}

void AShip::BeginPlay()
{
	//фунция отца
	Super::BeginPlay();

	//начальный таймер и материал
	GetWorld()->GetTimerManager().SetTimer(Shoot_in_the_Dark, this, &AShip::Start_Fire, Shoot_Interval, true, 0.f);
	ShipMaterial = ShipMesh->GetMaterial(0);
}

void AShip::DestroyShip_Implementation()
{
	//отключаем каллизию
	SetActorEnableCollision(false);

	//очищаем бинды
	ShipInputComponent->ClearActionBindings();

	//останавливаем стрельбу
	ShootComponent->StopShotting();
	GetWorld()->GetTimerManager().ClearTimer(Shoot_in_the_Dark);//очищаем таймер

	CameraShake(1.5f);//насколько трясем 

	ShipMesh->SetMaterial(0, RecoverMat);//материал стамины

	//отключаем партиклы, если они есть
	if (DestroyParticle)UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyParticle, GetActorTransform(), true);

	//цикл отключения партиколов
	for (UActorComponent* Component : GetComponentsByClass(UParticleSystemComponent::StaticClass()))
	{
		Component->Deactivate();
	}

}

void AShip::RecoverShip_Implementation()
{
	//активация каллизии
	SetActorEnableCollision(true);
	//восстановление биндов выстрелов
	ShipInputComponent->BindAction(FireBinding, IE_Pressed, this, &AShip::Start_Fire);
	ShipInputComponent->BindAction(FireBinding, IE_Released, this, &AShip::End_Fire); 
	ShipInputComponent->BindAction(AutoFireBinding, IE_Pressed, this, &AShip::Auto_Fire);
	ShootComponent->StartShotting();
	//установка таймера
	GetWorld()->GetTimerManager().SetTimer(Shoot_in_the_Dark, this, &AShip::Auto_Fire, Shoot_Interval, true, 0.f);
	
	//установка материала корабля
	ShipMesh->SetMaterial(0, ShipMaterial);
	//цикл партиколов
	for (UActorComponent* Component : GetComponentsByClass(UParticleSystemComponent::StaticClass()))
	{
		Component->Activate(true);
	}
}

float AShip::TakeDamage(float Damage, const FDamageEvent& DamageEvent, AController* Instigat, AActor* DamageCauser)
{
	//если не возможно нанести урон возращает 0.f
	if (!CanBeDamaged())return 0.f;
	if (DestoySound != nullptr)//если есть звук - он проиграется
	{
		UGameplayStatics::PlaySoundAtLocation(this, DestoySound, GetActorLocation());
	}
	//возращаем нанесенный урон
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
	//возможно ли нансти урон
	return bCanBeDamaged;
	
}

void AShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//устаналиваем направления вперед-назад и вправо-влево 
	const float ForwardValue = GetInputAxisValue(MoveForwardBinding);
	const float RightValue = GetInputAxisValue(MoveRightBinding);

	//получаем нынешнее направление
	const FVector MoveDirection = FVector(ForwardValue, RightValue, 0.f).GetClampedToMaxSize(1.0f);
	//создаем скорость
	const FVector Movement = MoveDirection * MoveSpeed * DeltaTime;

	//если персонаж двигается
	if (Movement.SizeSquared() > 0.0f)
	{
		//получаем нынешнее расположение
		FVector NewLocation = GetActorLocation();
		//границы для игрока по XY
		NewLocation.X = FMath::Clamp(NewLocation.X + MoveDirection.Y, -1050.f, 1250.f);
		NewLocation.Y = FMath::Clamp(NewLocation.Y + MoveDirection.X, -1700.f, 1700.f);
		//устанавливаем границы
		SetActorLocation(NewLocation);
		//создаем структру поворотов
		const FRotator NewRotation = Movement.Rotation();
		FHitResult Hit(1.f);
		//устанавливаем напрвление в следующих кадрах
		RootComponent->MoveComponent(Movement, NewRotation, true, &Hit);
		if (Hit.IsValidBlockingHit())//проверка 2D направления
		{
			const FVector Normal2D = Hit.Normal.GetSafeNormal2D();
			const FVector Deflection = FVector::VectorPlaneProject(Movement, Normal2D) * (1.f - Hit.Time);
			RootComponent->MoveComponent(Deflection, NewRotation, true);
		}
	}
}
