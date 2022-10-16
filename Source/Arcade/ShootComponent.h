
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"//��������� �������� ,����������� ����� UE4
#include <Arcade/Projectail.h>
#include "ShootComponent.generated.h"

//��������� ���������
USTRUCT(BlueprintType)
struct FShoot_inf
{
	GENERATED_BODY()
public:
	UPROPERTY(Category = "Shoot", EditAnywhere, BlueprintReadWrite)
		FVector GunOffset;//���������� 
	UPROPERTY(Category = "Shoot", EditAnywhere, BlueprintReadWrite)
		float Angle;//����
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shoot")
		TSubclassOf<AProjectail> Project_Class;//������ ����������� ������ Projectail'�� 

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shoot")
		float Damage;//����

};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ARCADE_API UShootComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UShootComponent();

protected:
	
	virtual void BeginPlay() override;
	void Fire_Shoot();//�������
	
	FTimerHandle Shoot_in_the_Dark;//�������� ��� �������

public:

	UFUNCTION(BlueprintCallable, Category = "Shoot")
		void StartShotting();//������ ���������

	UFUNCTION(BlueprintCallable, Category = "Shoot")
		void StopShotting();//����� ���������

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shoot")
		float Shoot_Interval;//�������� 

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shoot")
     TArray<FShoot_inf>Shoot_infs;//������ �� ��������� 

};
