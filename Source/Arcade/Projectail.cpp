
#include "Projectail.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/DamageType.h"//DamageType ������������ ��� ����������� � �������� ���������� ����� ������ � �������������� ����������� ��� ��������� ������� �� ����� �� ��������� ����������.
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

	Project_Move->InitialSpeed = 4000.f;//����������� ��������
	Project_Move->MaxSpeed = 4500.f;//������������ ��������

	Project_Move->ProjectileGravityScale = 0.f;//���������� ��������
	InitialLifeSpan = 3.0f;//���� �����
}

void AProjectail::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner())//���� ������� ����������
	{
		UBoxComponent* OwnerCollis = GetOwner()->FindComponentByClass<UBoxComponent>();//������� �� ������ �������,������� ��� ���������
		Project_Collis->IgnoreComponentWhenMoving(OwnerCollis, true);
		OwnerCollis->IgnoreComponentWhenMoving(Project_Collis, true);

		Project_Collis->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	//��������� �������� �� �������
	Project_Collis->OnComponentBeginOverlap.AddDynamic(this,&AProjectail::OnProjectailOverlap);
}

void AProjectail::OnProjectailOverlap(UPrimitiveComponent* OpelappedComp,AActor* OtherActor,UPrimitiveComponent* OtherCom,int32 BodyIndex,bool Sweep,const FHitResult & Hit)
{
	//���� �� ���������� ������ �������� : ����� �� �������
	if (!OtherActor || !Cast<APawn>(OtherActor))return;
	
	if (!GetOwner())return;
	APawn* PawnOwner = Cast<APawn>(GetOwner());
	if(!PawnOwner)return;//���� �� ���������� Pawn'a
	AController* Instigat = PawnOwner->GetController();
	//��������� ���� � ������� ����������� ������� UE4
	UGameplayStatics::ApplyDamage(OtherActor, Damage, Instigat, this, UDamageType::StaticClass());
	Destroy();
}

void AProjectail::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//����������� ��������
	AddActorLocalOffset(FVector(Projectil_Speed * DeltaTime, 0.f, 0.f));
}

