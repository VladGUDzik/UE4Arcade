
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
	
	//���������� � ������������ ����������� ������
	EnemySpawnComponent = CreateDefaultSubobject<UEnemySpawnComponent>(TEXT("EnemySpawnComponent"));

	LIVE_Component = CreateDefaultSubobject<ULIVE_Component>(TEXT("LIVE_Component"));
}

void AArcadeGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	LIVE_Component->HealthsEnded.AddDynamic(this, &AArcadeGameModeBase::EndGame);
	//������� ���������� � ������������ ����������� ������
	Ship = Cast<AShip>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (!Ship)return;//���� ������� ���������� 

	ChangeShootLevel(true);//����� ������ ������� 

	Ship->PawnDamage.AddDynamic(this, &AArcadeGameModeBase::DestroyShip);//������ ������ ����������
	GetWorld()->GetTimerManager().SetTimer(IncreaseDifTimer, this, &AArcadeGameModeBase::IncreaseDifficulty, IncreaseDifficultyTime, true);
}

void AArcadeGameModeBase::DestroyShip_Implementation()
{
	Ship->DestroyShip();//����������� �������
	LIVE_Component->ChangeHealths(-1);//��������� ������ �������
	ChangeShootLevel(false);//������ ����� ������

	if (!IsGameOver)//���� �� ����� ����
	{
		GetWorld()->GetTimerManager().SetTimer(RecoverTimer, this, &AArcadeGameModeBase::RecoverShip, ShipRecoverTime, false);//����� �������������� �������
	}
}

void AArcadeGameModeBase::RecoverShip_Implementation()
{
	//�������������� ��������
	Ship->RecoverShip();
}

void AArcadeGameModeBase::EndGame()
{
	IsGameOver = true;
	//���� ����� ���� ��������� ����� ����������� � ���������� �������
	EnemySpawnComponent->SetActive(false);
	GameOver.Broadcast();
	UGameplayStatics::GetPlayerPawn(this, 0)->Destroy();
	
}

void AArcadeGameModeBase::IncreaseDifficulty()
{
	EnemySpawnComponent->ChangeStageTimeMultiplier = FMath::Max(EnemySpawnComponent->ChangeStageTimeMultiplier * 0.95, 0.4);//������ �� ������������ ��������
}

void AArcadeGameModeBase::AddHealth(int Health)
{
	//��������� ������
	LIVE_Component->ChangeHealths(Health);
}

bool AArcadeGameModeBase::ChangeShootLevel(bool Up)
{
	Ship = Cast<AShip>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (!Ship)return false;

	//��������� ������� ��� �������� ������� ��������� ������
	int NewLevel = FMath::Clamp(CurrentShootLevel + (Up ? 1 : -1), 0, Shoot_infLevels.Num() - 1);

	if (NewLevel == CurrentShootLevel)return false;

	CurrentShootLevel = NewLevel;
	//��������� ��� ��������� ��������
	Ship->ShootComponent->Shoot_infs = Shoot_infLevels[CurrentShootLevel].Shoot_infs;

	return true;
}




