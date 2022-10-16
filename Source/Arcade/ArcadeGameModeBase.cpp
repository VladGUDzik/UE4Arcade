
#include "ArcadeGameModeBase.h"
#include"Engine/World.h"
#include"TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Arcade/Ship.h"
#include "Sound/SoundBase.h"


AArcadeGameModeBase::AArcadeGameModeBase()
	:
	ShipRecoverTime(3.f),
	CurrentShootLevel(-1),
	IncreaseDifficultyTime(1.f)
{
	IsGameOver = false;
	
	//переменная с функционалом самописного класса
	EnemySpawnComponent = CreateDefaultSubobject<UEnemySpawnComponent>(TEXT("EnemySpawnComponent"));

	LIVE_Component = CreateDefaultSubobject<ULIVE_Component>(TEXT("LIVE_Component"));
}

void AArcadeGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	LIVE_Component->HealthsEnded.AddDynamic(this, &AArcadeGameModeBase::EndGame);
	//создаем переменную с функционалом самописного класса
	Ship = Cast<AShip>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (!Ship)return;//если корабль существует 

	ChangeShootLevel(true);//смена уровня стрелбы 

	Ship->PawnDamage.AddDynamic(this, &AArcadeGameModeBase::DestroyShip);//фунцию делаем динамичной
	GetWorld()->GetTimerManager().SetTimer(IncreaseDifTimer, this, &AArcadeGameModeBase::IncreaseDifficulty, IncreaseDifficultyTime, true);
}

void AArcadeGameModeBase::DestroyShip_Implementation()
{
	Ship->DestroyShip();//уничтожение корабля
	LIVE_Component->ChangeHealths(-1);//отнимание жизней корабля
	ChangeShootLevel(false);//отмена смены уровня

	if (!IsGameOver)//если не конец игры
	{
		GetWorld()->GetTimerManager().SetTimer(RecoverTimer, this, &AArcadeGameModeBase::RecoverShip, ShipRecoverTime, false);//время восстановления корабля
	}
}

void AArcadeGameModeBase::RecoverShip_Implementation()
{
	//восстановления клорабля
	Ship->RecoverShip();
}

void AArcadeGameModeBase::EndGame()
{
	IsGameOver = true;
	//если конец игры отключаем спаун противников и уничтожаем корабль
	EnemySpawnComponent->SetActive(false);
	GameOver.Broadcast();
	UGameplayStatics::GetPlayerPawn(this, 0)->Destroy();
	
}

void AArcadeGameModeBase::IncreaseDifficulty()
{
	EnemySpawnComponent->ChangeStageTimeMultiplier = FMath::Max(EnemySpawnComponent->ChangeStageTimeMultiplier * 0.95, 0.4);//Таймер на максимальное значение
}

void AArcadeGameModeBase::AddHealth(int Health)
{
	//изменение жизней
	LIVE_Component->ChangeHealths(Health);
}

bool AArcadeGameModeBase::ChangeShootLevel(bool Up)
{
	Ship = Cast<AShip>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (!Ship)return false;

	//тернарное условие для проверки условий повышения уровня
	int NewLevel = FMath::Clamp(CurrentShootLevel + (Up ? 1 : -1), 0, Shoot_infLevels.Num() - 1);

	if (NewLevel == CurrentShootLevel)return false;

	CurrentShootLevel = NewLevel;
	//улучшение или ухудшение стрельбы
	Ship->ShootComponent->Shoot_infs = Shoot_infLevels[CurrentShootLevel].Shoot_infs;

	return true;
}




