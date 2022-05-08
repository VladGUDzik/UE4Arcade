
#include "EnemySpawnComponent.h"
#include"Engine/World.h"
#include"TimerManager.h"


void UEnemySpawnComponent::BeginPlay()
{
	Super::BeginPlay();

	Random.GenerateNewSeed();//������������
	StartSpawnStage();
}

void UEnemySpawnComponent::StartSpawnStage()
{
	Currect_Stage = Spawn_Stages[Random.FRandRange(0, Spawn_Stages.Num()-1)];//�������� ������
	EnemiesSpawn=0;//��������� �������� 
	SpawnEnemy();

	float ChangeSt_Time = Random.FRandRange(StageMinDelay, StageMaxDelay)*ChangeStageTimeMultiplier;//����� ������
	GetWorld()->GetTimerManager().SetTimer(ChangeStageTimer, this, &UEnemySpawnComponent::StartSpawnStage, ChangeSt_Time, false);
}

void UEnemySpawnComponent::Deactivate()
{
	//����������� ������� � ������
	Super::Deactivate();

	GetWorld()->GetTimerManager().ClearTimer(ChangeStageTimer);
	GetWorld()->GetTimerManager().ClearTimer(SpawnEnemyTimer);
}

void UEnemySpawnComponent::SpawnEnemy()
{
	//���������� �� ������� ������
	FActorSpawnParameters SpawnParameters;
	GetWorld()->SpawnActor<AEnemy_Pawn>(Currect_Stage.Enemy_Class, Currect_Stage.Spawn_Trans, SpawnParameters);
	//���������� ���������� ������
	EnemiesSpawn++;
	if (EnemiesSpawn < Currect_Stage.Count_Enemy)
	{
		GetWorld()->GetTimerManager().SetTimer(SpawnEnemyTimer, this, &UEnemySpawnComponent::SpawnEnemy, Currect_Stage.SpawnDelay, false);
	}
}

