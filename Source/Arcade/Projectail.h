
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include"Components/SphereComponent.h"//каллизи€ выстрела
#include "GameFramework/ProjectileMovementComponent.h"// компонент контрол€ направлени€ и движени€ выстрелов
#include "Projectail.generated.h"

UCLASS()
class ARCADE_API AProjectail : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AProjectail();

protected:
	
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Game"/*в скобках по вопросом*/)//функци€ с логикой,что происходит при столкновении
	void OnProjectailOverlap(UPrimitiveComponent* OpelappedComp, AActor* OtherActor, UPrimitiveComponent* OtherCom, int32 BodyIndex, bool Sweep, const FHitResult& Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shoot")
	USphereComponent* Project_Collis;//каллизи€ сферы
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shoot")
	UStaticMeshComponent* Mesh;//модель выстрела


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shoot")
	UProjectileMovementComponent* Project_Move;//класс движени€ выстрелов

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shoot")
		float Projectil_Speed;//скорость выстрелов

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shoot")
		float Damage;//урон
};
