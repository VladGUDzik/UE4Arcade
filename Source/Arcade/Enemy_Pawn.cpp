
#include "Enemy_Pawn.h"
#include "Kismet/GameplayStatics.h"
#include"Components/StaticMeshComponent.h"
//#include "ArcadeGameModeBase.h"
#include "Arcade_GameInstance.h"
#include "Engine/World.h"
#include "Sound/SoundBase.h"
#include"TimerManager.h"

AEnemy_Pawn::AEnemy_Pawn()
	:
	Shoot_Interval(0.5f)
{
	PrimaryActorTick.bCanEverTick = true;

	EnemyCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("EnemyCollision"));
	SetRootComponent(EnemyCollision);
	EnemyCollision->SetCollisionProfileName("Pawn");

	EnemyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EnemyMesh"));
	EnemyMesh->SetupAttachment(EnemyCollision);
	EnemyMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ShootComponent = CreateDefaultSubobject<UShootComponent>(TEXT("ShootComponent"));
	Health_Component = CreateDefaultSubobject<UHealth_Component>(TEXT("Health_Component"));

	InitialLifeSpan = 40.0f;

}

void AEnemy_Pawn::BeginPlay()
{
	Super::BeginPlay();
	//добавляем динамики на функцию
	Health_Component->OnHealthEnded.AddDynamic(this, &AEnemy_Pawn::KillPawn);
	OnActorBeginOverlap.AddDynamic(this, &AEnemy_Pawn::OnEnemyOverlap);
    //таймер выстрелов
	GetWorld()->GetTimerManager().SetTimer(Shoot_in_the_Dark, this, &AEnemy_Pawn::Fire, Shoot_Interval, true, 0.f);

}

void AEnemy_Pawn::KillPawn()
{
	//получаем в переменной фунцтонал ArcadeGameModeBase
	UArcade_GameInstance* GameInstance= Cast<UArcade_GameInstance>(UGameplayStatics::GetGameInstance(this));
	//AArcadeGameModeBase* Gamemode = Cast<AArcadeGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (GameInstance)//если не конец игры , добавляем поинты
	{
		GameInstance->AddPoints(DestroyPoint);
	}
	SpawnBonuses();//спаун бонусов

	DestroyPawn();//уничтожение кораблей
}

void AEnemy_Pawn::Fire()
{
	if (FireSound != nullptr)//звук выстрелов
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}
}

void AEnemy_Pawn::DestroyPawn()
{
	//эффект уничтожения корабля
	if (DestroyParticle)UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyParticle, GetActorTransform(), true);
	if (DectroySound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DectroySound, GetActorLocation());
	}
	Destroy();
}

void AEnemy_Pawn::OnEnemyOverlap(AActor* OverlapedActor, AActor* OtherActor)
{
	if (OtherActor != UGameplayStatics::GetPlayerPawn(this, 0))return;

	float AppliedDamage = UGameplayStatics::ApplyDamage(OtherActor, 100.f, GetController(), this, UDamageType::StaticClass());
	if (AppliedDamage > 0.f) DestroyPawn();
}


void AEnemy_Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	float WorldMoveOffset = -100.f * DeltaTime;  //Ускоряем корабли
	AddActorWorldOffset(FVector(WorldMoveOffset, 0.f, 0.f));
	
}

void AEnemy_Pawn::SpawnBonuses()
{
	//если шанс бонуса больше рандомного шанса спауним бонус
	FRandomStream Random;
	Random.GenerateNewSeed();
	FActorSpawnParameters SpawnParam;
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	float RandChance;
	for (FBonusChance Bonus : PossibleBonus)
	{
		RandChance = Random.RandRange(0.f, 100.f);
		if (RandChance < Bonus.Chance)
		{
			GetWorld()->SpawnActor<ABonus>(Bonus.Bonus_Class, GetActorLocation(), FRotator(0.f), SpawnParam);
		}
	}
}
