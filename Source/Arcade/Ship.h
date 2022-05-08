
#pragma once

#include "CoreMinimal.h"//Включен в стандартный класс UObjectBase
#include "GameFramework/SpringArmComponent.h"//библиотека для фиксации камеры и её расстояния
#include "Camera/CameraComponent.h"//камера игрока
#include"Components/BoxComponent.h"//каллизия корабля игрока
#include "GameFramework/Pawn.h"//Pawn — это базовый класс всех действующих лиц, которыми могут обладать игроки или противник. Они являются физическими представлениями игроков и существ на уровне.
#include "Arcade/ShootComponent.h"//самописная библиотека с свойствами стреляющего компонента
#include "Ship.generated.h"//рендер(создание) самой модели корабля

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPawnDamageEvent);
DECLARE_DELEGATE_OneParam(FShakeDelegate, float);//

UCLASS()
class ARCADE_API AShip : public APawn
{
	GENERATED_BODY()

public:
	// Устанавливаем стандартные переменные
	AShip();//конструктор

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		float MoveSpeed;//скорость корабля

	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
		class USoundBase* FireSound;// структура звуков выстрелов

	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
		class USoundBase* DestoySound;// структура звуков уничтожения
protected:
	// функция вызывается при начале игры или спауне игрока
	virtual void BeginPlay() override;

	//константные названия биндов на клавиши
	static const FName MoveForwardBinding;
	static const FName MoveRightBinding;
	static const FName FireBinding;
	static const FName AutoFireBinding;

	//структура для создания таймера
	FTimerHandle Shoot_in_the_Dark;

	//Функция для возвращения входящего урона
	virtual float TakeDamage(float Damage, const FDamageEvent& DamageEvent, AController* Instigat, AActor* DamageCauser)override;
private:
	//класс стандартного материала корабля
	UMaterialInterface* ShipMaterial;
	
	UFUNCTION()
		void CameraShake(float Scale);//Вызываем тряску камеры

	public:
	// функция что вызывается каждый кадр
	virtual void Tick(float DeltaTime) override;

	// фунция устанавливает инпуты на клавиши
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	//функция уничтожения корабля 
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "LIVE")
		void DestroyShip();
	void DestroyShip_Implementation();//функция совместимая с BP

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "LIVE")
		void RecoverShip();// функция для восстановления стамины корабля
	void RecoverShip_Implementation();

	UFUNCTION(BlueprintPure,BlueprintNativeEvent, Category = "LIVE")
		bool CanBeDamaged();// функция для проверки возможности нанесения урона
	bool CanBeDamaged_Implementation();

	//функции для начала, конца и автоматической стрельбы
	void Start_Fire();
	void End_Fire();
	void Auto_Fire();

	//классы UE4
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ship")
		UStaticMeshComponent* ShipMesh;//модель корабля
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ship")
		UBoxComponent* ShipCollision;//каллизия корабля
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ship")
		UCameraComponent* CameraComponent;//камера игрока
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ship")
		USpringArmComponent* CameraBoom;//класс для установки угла, расстояния камеры

	UInputComponent* ShipInputComponent;//инпуты

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shoot")
		UShootComponent* ShootComponent;//самописный класс с свойствами выстрелов

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ship")
		UMaterialInterface* RecoverMat;//материал,который применяется при восстановлениеии стамины

	bool bCanBeDamaged ;//поврежден или не поврежнен

	UPROPERTY(BlueprintAssignable, Category = "LIVE")
		FPawnDamageEvent PawnDamage;//класс для нанесения урона

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Visual")
		UParticleSystem* DestroyParticle;//эффект взрыва

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shoot")
		float Shoot_Interval;//интервал автоматической мтрельбы
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Camera")
		TSubclassOf<UMatineeCameraShake> CamShake;//переменной передаем функционал класса

};
