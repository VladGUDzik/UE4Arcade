
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Arcade/EnemySpawnComponent.h"//���������� ������ ������ ������
#include "Arcade/LIVE_Component.h"//���������� ������ ����� �������
#include "Arcade/ShootComponent.h"
#include "ArcadeGameModeBase.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameOverEvent);//��������� ��� �������� ������������ ��������������

//���������
USTRUCT(BlueprintType)
struct FShoot_infLevel
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Shoot")
		TArray<FShoot_inf> Shoot_infs;//������ �� ��������� ��������� �� ����������� ������
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
		bool IsGameOver;//���������� ����� ����

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemies")
	UEnemySpawnComponent* EnemySpawnComponent;//�������� ���������� � ������������ ����������� ������

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LIVES")
	ULIVE_Component* LIVE_Component;//�������� ���������� � ������������ ����������� ������

	UPROPERTY(BlueprintAssignable, Category = "Game")
	FGameOverEvent GameOver;//��������� � ���������� �����������

	UFUNCTION(BlueprintCallable, Category = "Game")
	void EndGame();//������� ����� ����

	UFUNCTION(BlueprintCallable, Category = "Game")
		void AddHealth(int Health);//���������� ������

	UFUNCTION(BlueprintCallable, Category = "Game")
	bool ChangeShootLevel(bool Up);//��������� ������ ��������

	UFUNCTION(BlueprintCallable, Category = "Game")
	void IncreaseDifficulty();//���������� ���������

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Game")
	float IncreaseDifficultyTime;//����� �������������� �������

	UPROPERTY(BlueprintReadWrite, Category = "Game")
		float ShipRecoverTime;//����� ����� ������� ��������� ����������

	UPROPERTY(BlueprintReadOnly, Category = "Game")
	class AShip* Ship;//�������� ���������� � ������������ ����������� ������ 

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Shoot")
	TArray<FShoot_infLevel> Shoot_infLevels;//������ �� ������� ��������

	UPROPERTY(BlueprintReadOnly, Category = "Shoot")
	int CurrentShootLevel;//�������� ������� ��������
};
