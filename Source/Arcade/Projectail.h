// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include"Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectail.generated.h"

UCLASS()
class ARCADE_API AProjectail : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectail();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shoot")
	USphereComponent* Project_Collis;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shoot")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shoot")
		UProjectileMovementComponent* Project_Move;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shoot")
		float Projectil_Speed;


};
