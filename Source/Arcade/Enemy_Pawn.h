// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include"Components/BoxComponent.h"
#include "Arcade/ShootComponent.h"
#include "Arcade/Health_Component.h"//самописный класс жизни врагов
#include "Arcade/Bonus.h"
#include "Enemy_Pawn.generated.h"

//структура бонусов
USTRUCT(BlueprintType)
struct FBonusChance
{
	GENERATED_BODY()
public:
	UPROPERTY(Category = "Bonus", EditAnywhere, BlueprintReadWrite)
	float Chance;//шанс
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bonus")
		TSubclassOf<ABonus> Bonus_Class;//массив из классов
};

UCLASS()
class ARCADE_API AEnemy_Pawn : public APawn
{
	GENERATED_BODY()

public:
	
	AEnemy_Pawn();

	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
		class USoundBase* DectroySound;

	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
		class USoundBase* FireSound;
protected:
	
	virtual void BeginPlay() override;

	void SpawnBonuses();//спаун бонусов

	UFUNCTION()
	void KillPawn();//убийство врагов
	
	UFUNCTION()
	void OnEnemyOverlap(AActor* OverlapedActor, AActor* OtherActor);//функция с логикой при пересечении каллизий
	
	UFUNCTION()
		void Fire();//выстрел 

	FTimerHandle Shoot_in_the_Dark;
public:	
	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ship")
		UStaticMeshComponent* EnemyMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ship")
		UBoxComponent* EnemyCollision;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shoot")
		UShootComponent* ShootComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health")
		UHealth_Component* Health_Component;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ship")
		int DestroyPoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Visual")
		UParticleSystem * DestroyParticle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bonus")
		TArray<FBonusChance>PossibleBonus;//массив стуктур

	UFUNCTION(BlueprintCallable,Category="Pawn")
		void DestroyPawn();//уничтожение врагов

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shoot")
		float Shoot_Interval;
};
