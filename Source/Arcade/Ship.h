// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h" 
#include "Camera/CameraComponent.h"
#include"Components/BoxComponent.h"
#include "GameFramework/Pawn.h"
#include "Arcade/ShootComponent.h"
#include "Ship.generated.h"


UCLASS()
class ARCADE_API AShip : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AShip();
	
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		float MoveSpeed;
	
protected:
	// Called when the game starts or when spawned
	
	static const FName MoveForwardBinding;
	static const FName MoveRightBinding;
	static const FName FireBinding;

private:
	
	bool bDead;
	bool bCanFire;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void Fire_Time();
	void End_Fire_Time();
	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ship")
	UStaticMeshComponent* ShipMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ship")
	UBoxComponent* ShipCollision;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ship")
	UCameraComponent* CameraComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ship")
	USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shoot")
	UShootComponent* ShootComponent;


};
