// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <Arcade/Projectail.h>
#include "ShootComponent.generated.h"

USTRUCT(BlueprintType)
struct FShoot_inf
{
	GENERATED_BODY()
public:
	UPROPERTY(Category = "Shoot", EditAnywhere, BlueprintReadWrite)
		FVector GunOffset;
	UPROPERTY(Category = "Shoot", EditAnywhere, BlueprintReadWrite)
		float Angle;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shoot")
		TSubclassOf<AProjectail> Project_Class;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ARCADE_API UShootComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UShootComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void Fire_Shoot();
	
	FTimerHandle Shoot_in_the_Dark;

public:

	UFUNCTION(BlueprintCallable, Category = "Shoot")
		void StartShotting();

	UFUNCTION(BlueprintCallable, Category = "Shoot")
		void StopShotting();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shoot")
		float Shoot_Interval;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shoot")
     TArray<FShoot_inf>Shoot_infs;

};
