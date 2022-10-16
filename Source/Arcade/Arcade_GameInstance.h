// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
//#include "Arcade/LIVE_Component.h"//добавление класса жизне корабля
#include "Arcade_GameInstance.generated.h"

/**
 *
 */
UCLASS()
class ARCADE_API UArcade_GameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UArcade_GameInstance();
	UFUNCTION(BlueprintCallable, Category = "Game")
		void AddPoints(int Points);//добавление очков

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LIVES")
	//	ULIVE_Component* LIVE_Component;//создание переменной с функционалом самописного класса

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
		int GamePoints;//игровые очки
};
