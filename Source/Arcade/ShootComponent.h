
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"//компонент родитель ,стандартный класс UE4
#include <Arcade/Projectail.h>
#include "ShootComponent.generated.h"

//структура выстрелов
USTRUCT(BlueprintType)
struct FShoot_inf
{
	GENERATED_BODY()
public:
	UPROPERTY(Category = "Shoot", EditAnywhere, BlueprintReadWrite)
		FVector GunOffset;//координаты 
	UPROPERTY(Category = "Shoot", EditAnywhere, BlueprintReadWrite)
		float Angle;//угол
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shoot")
		TSubclassOf<AProjectail> Project_Class;//массив самописного класса Projectail'ов 

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shoot")
		float Damage;//урон

};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ARCADE_API UShootComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UShootComponent();

protected:
	
	virtual void BeginPlay() override;
	void Fire_Shoot();//выстрел
	
	FTimerHandle Shoot_in_the_Dark;//сруктура для таймера

public:

	UFUNCTION(BlueprintCallable, Category = "Shoot")
		void StartShotting();//начало выстрелов

	UFUNCTION(BlueprintCallable, Category = "Shoot")
		void StopShotting();//конец выстрелов

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shoot")
		float Shoot_Interval;//интервал 

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shoot")
     TArray<FShoot_inf>Shoot_infs;//массив из структуры 

};
