
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Arcade/Enemy_Pawn.h"
#include "EnemySpawnComponent.generated.h"

//структура противников
USTRUCT(BlueprintType)
struct FEnemy_Spawn_inf
{
	GENERATED_BODY()
public:
	
	UPROPERTY(Category = "Enemies", EditAnywhere, BlueprintReadWrite)
		FTransform Spawn_Trans;//позиция противника
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemies")
		TSubclassOf<AEnemy_Pawn> Enemy_Class = AEnemy_Pawn::StaticClass();//массив врагов

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemies")
		int Count_Enemy;//количество противников
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemies")
		float SpawnDelay;//промежуток спауна
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARCADE_API UEnemySpawnComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	
	virtual void BeginPlay() override;
	//стандартная функция деактивации
	virtual void Deactivate()override;
	//спаун врагов
	void SpawnEnemy();
	//стадии спауна
	void StartSpawnStage();

	//структура стадий
	FEnemy_Spawn_inf Currect_Stage;
	//номер стадии
	int EnemiesSpawn;

	FTimerHandle ChangeStageTimer;
	FTimerHandle SpawnEnemyTimer;
	//рандом
	FRandomStream Random;

public:	
	//массив стуктур
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemies")
	TArray<FEnemy_Spawn_inf>Spawn_Stages;
		
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemies")
	float StageMinDelay;//минимальное расстояние спауна

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemies")
	float StageMaxDelay;//максимальное расстояние спауна

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemies")
		float ChangeStageTimeMultiplier;//изменение сложности


};
