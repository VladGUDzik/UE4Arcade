
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Arcade/Enemy_Pawn.h"
#include "EnemySpawnComponent.generated.h"

//��������� �����������
USTRUCT(BlueprintType)
struct FEnemy_Spawn_inf
{
	GENERATED_BODY()
public:
	
	UPROPERTY(Category = "Enemies", EditAnywhere, BlueprintReadWrite)
		FTransform Spawn_Trans;//������� ����������
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemies")
		TSubclassOf<AEnemy_Pawn> Enemy_Class = AEnemy_Pawn::StaticClass();//������ ������

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemies")
		int Count_Enemy;//���������� �����������
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemies")
		float SpawnDelay;//���������� ������
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARCADE_API UEnemySpawnComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	
	virtual void BeginPlay() override;
	//����������� ������� �����������
	virtual void Deactivate()override;
	//����� ������
	void SpawnEnemy();
	//������ ������
	void StartSpawnStage();

	//��������� ������
	FEnemy_Spawn_inf Currect_Stage;
	//����� ������
	int EnemiesSpawn;

	FTimerHandle ChangeStageTimer;
	FTimerHandle SpawnEnemyTimer;
	//������
	FRandomStream Random;

public:	
	//������ �������
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemies")
	TArray<FEnemy_Spawn_inf>Spawn_Stages;
		
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemies")
	float StageMinDelay;//����������� ���������� ������

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemies")
	float StageMaxDelay;//������������ ���������� ������

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemies")
		float ChangeStageTimeMultiplier;//��������� ���������


};
