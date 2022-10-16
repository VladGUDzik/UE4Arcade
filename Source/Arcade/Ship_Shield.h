// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ship_Shield.generated.h"

class AShip;

UCLASS()
class ARCADE_API AShip_Shield : public AActor
{
	GENERATED_BODY()
	
protected:

	FTimerHandle ShieldTimer;
	class AShip* ShieldforShip;
public:	
	// Sets default values for this actor's properties
	AShip_Shield();

	UFUNCTION(BlueprintCallable, Category = "Shield")
		void ActivateShield(AShip* Ship);

	UFUNCTION(BlueprintCallable, Category = "Shield")
		void DeactivateShield();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shield")
		float ShieldTime;

};
