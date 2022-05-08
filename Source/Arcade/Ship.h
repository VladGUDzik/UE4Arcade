
#pragma once

#include "CoreMinimal.h"//������� � ����������� ����� UObjectBase
#include "GameFramework/SpringArmComponent.h"//���������� ��� �������� ������ � � ����������
#include "Camera/CameraComponent.h"//������ ������
#include"Components/BoxComponent.h"//�������� ������� ������
#include "GameFramework/Pawn.h"//Pawn � ��� ������� ����� ���� ����������� ���, �������� ����� �������� ������ ��� ���������. ��� �������� ����������� ��������������� ������� � ������� �� ������.
#include "Arcade/ShootComponent.h"//���������� ���������� � ���������� ����������� ����������
#include "Ship.generated.h"//������(��������) ����� ������ �������

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPawnDamageEvent);
DECLARE_DELEGATE_OneParam(FShakeDelegate, float);//

UCLASS()
class ARCADE_API AShip : public APawn
{
	GENERATED_BODY()

public:
	// ������������� ����������� ����������
	AShip();//�����������

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		float MoveSpeed;//�������� �������

	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
		class USoundBase* FireSound;// ��������� ������ ���������

	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
		class USoundBase* DestoySound;// ��������� ������ �����������
protected:
	// ������� ���������� ��� ������ ���� ��� ������ ������
	virtual void BeginPlay() override;

	//����������� �������� ������ �� �������
	static const FName MoveForwardBinding;
	static const FName MoveRightBinding;
	static const FName FireBinding;
	static const FName AutoFireBinding;

	//��������� ��� �������� �������
	FTimerHandle Shoot_in_the_Dark;

	//������� ��� ����������� ��������� �����
	virtual float TakeDamage(float Damage, const FDamageEvent& DamageEvent, AController* Instigat, AActor* DamageCauser)override;
private:
	//����� ������������ ��������� �������
	UMaterialInterface* ShipMaterial;
	
	UFUNCTION()
		void CameraShake(float Scale);//�������� ������ ������

	public:
	// ������� ��� ���������� ������ ����
	virtual void Tick(float DeltaTime) override;

	// ������ ������������� ������ �� �������
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	//������� ����������� ������� 
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "LIVE")
		void DestroyShip();
	void DestroyShip_Implementation();//������� ����������� � BP

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "LIVE")
		void RecoverShip();// ������� ��� �������������� ������� �������
	void RecoverShip_Implementation();

	UFUNCTION(BlueprintPure,BlueprintNativeEvent, Category = "LIVE")
		bool CanBeDamaged();// ������� ��� �������� ����������� ��������� �����
	bool CanBeDamaged_Implementation();

	//������� ��� ������, ����� � �������������� ��������
	void Start_Fire();
	void End_Fire();
	void Auto_Fire();

	//������ UE4
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ship")
		UStaticMeshComponent* ShipMesh;//������ �������
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ship")
		UBoxComponent* ShipCollision;//�������� �������
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ship")
		UCameraComponent* CameraComponent;//������ ������
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ship")
		USpringArmComponent* CameraBoom;//����� ��� ��������� ����, ���������� ������

	UInputComponent* ShipInputComponent;//������

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shoot")
		UShootComponent* ShootComponent;//���������� ����� � ���������� ���������

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ship")
		UMaterialInterface* RecoverMat;//��������,������� ����������� ��� ���������������� �������

	bool bCanBeDamaged ;//��������� ��� �� ���������

	UPROPERTY(BlueprintAssignable, Category = "LIVE")
		FPawnDamageEvent PawnDamage;//����� ��� ��������� �����

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Visual")
		UParticleSystem* DestroyParticle;//������ ������

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shoot")
		float Shoot_Interval;//�������� �������������� ��������
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Camera")
		TSubclassOf<UMatineeCameraShake> CamShake;//���������� �������� ���������� ������

};
