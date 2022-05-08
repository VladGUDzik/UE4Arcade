
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Arcade/EnemySpawnComponent.h"//добавление класса спауна врагов
#include "Arcade/LIVE_Component.h"//добавление класса жизне корабля
#include "Arcade/ShootComponent.h"
#include "ArcadeGameModeBase.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameOverEvent);//диспатчер для создания динамических взаимодействий

//структура
USTRUCT(BlueprintType)
struct FShoot_infLevel
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Shoot")
		TArray<FShoot_inf> Shoot_infs;//массив из структуры Выстрелов из самописного класса
};

UCLASS()
class ARCADE_API AArcadeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AArcadeGameModeBase();
	virtual void BeginPlay()override;
protected:

	UFUNCTION(BlueprintNativeEvent,Category = "Game")
	void DestroyShip();
	void DestroyShip_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "Game")
	void RecoverShip();
	void RecoverShip_Implementation();

	FTimerHandle RecoverTimer;
	FTimerHandle IncreaseDifTimer;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
		bool IsGameOver;//переменная конца игры

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemies")
	UEnemySpawnComponent* EnemySpawnComponent;//создание переменной с функционалом самописного класса

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LIVES")
	ULIVE_Component* LIVE_Component;//создание переменной с функционалом самописного класса

	UPROPERTY(BlueprintAssignable, Category = "Game")
	FGameOverEvent GameOver;//структура с динамичным функционалм

	UFUNCTION(BlueprintCallable, Category = "Game")
	void EndGame();//Функция конца игры

	UFUNCTION(BlueprintCallable, Category = "Game")
		void AddHealth(int Health);//добавление жизней

	UFUNCTION(BlueprintCallable, Category = "Game")
	bool ChangeShootLevel(bool Up);//изменение уровня стрельбы

	UFUNCTION(BlueprintCallable, Category = "Game")
	void IncreaseDifficulty();//увеличение сложности

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Game")
	float IncreaseDifficultyTime;//время восстановления корабля

	UPROPERTY(BlueprintReadWrite, Category = "Game")
		float ShipRecoverTime;//время через которое сложность повышается

	UPROPERTY(BlueprintReadOnly, Category = "Game")
	class AShip* Ship;//создание переменной с функционалом самописного класса 

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Shoot")
	TArray<FShoot_infLevel> Shoot_infLevels;//массив из уровней стрельбы

	UPROPERTY(BlueprintReadOnly, Category = "Shoot")
	int CurrentShootLevel;//нынешний уровень стрельбы
};
