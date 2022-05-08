
#include "Projectail.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/DamageType.h"//DamageType предназначен для определения и описания конкретной формы ущерба и предоставления возможности для настройки реакций на ущерб из различных источников.
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"


// Sets default values
AProjectail::AProjectail()
	:
	Projectil_Speed(120.f)
{
 	
	PrimaryActorTick.bCanEverTick = true;

	Project_Collis = CreateDefaultSubobject<USphereComponent>(TEXT("Project_Collis"));
	SetRootComponent(Project_Collis);
	Project_Collis->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Project_Collis);
	Project_Move= CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Project_Move"));
	Mesh->SetCollisionProfileName("NoCollision");

	Project_Move->InitialSpeed = 4000.f;//изначальная скорость
	Project_Move->MaxSpeed = 4500.f;//максимальная скорость

	Project_Move->ProjectileGravityScale = 0.f;//гравитация выстрела
	InitialLifeSpan = 3.0f;//срок жизни
}

void AProjectail::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner())//если выстрел существует
	{
		UBoxComponent* OwnerCollis = GetOwner()->FindComponentByClass<UBoxComponent>();//Патроны не вредят кораблю,который ими выстрелил
		Project_Collis->IgnoreComponentWhenMoving(OwnerCollis, true);
		OwnerCollis->IgnoreComponentWhenMoving(Project_Collis, true);

		Project_Collis->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	//добавляем динамики на функцию
	Project_Collis->OnComponentBeginOverlap.AddDynamic(this,&AProjectail::OnProjectailOverlap);
}

void AProjectail::OnProjectailOverlap(UPrimitiveComponent* OpelappedComp,AActor* OtherActor,UPrimitiveComponent* OtherCom,int32 BodyIndex,bool Sweep,const FHitResult & Hit)
{
	//если не существует модели выстрела : выход из функции
	if (!OtherActor || !Cast<APawn>(OtherActor))return;
	
	if (!GetOwner())return;
	APawn* PawnOwner = Cast<APawn>(GetOwner());
	if(!PawnOwner)return;//если не существует Pawn'a
	AController* Instigat = PawnOwner->GetController();
	//добавляем урон с помощью стандартной функции UE4
	UGameplayStatics::ApplyDamage(OtherActor, Damage, Instigat, this, UDamageType::StaticClass());
	Destroy();
}

void AProjectail::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//направление выстрела
	AddActorLocalOffset(FVector(Projectil_Speed * DeltaTime, 0.f, 0.f));
}

