
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include"Components/SphereComponent.h"//�������� ��������
#include "GameFramework/ProjectileMovementComponent.h"// ��������� �������� ����������� � �������� ���������
#include "Projectail.generated.h"

UCLASS()
class ARCADE_API AProjectail : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AProjectail();

protected:
	
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Game"/*� ������� �� ��������*/)//������� � �������,��� ���������� ��� ������������
	void OnProjectailOverlap(UPrimitiveComponent* OpelappedComp, AActor* OtherActor, UPrimitiveComponent* OtherCom, int32 BodyIndex, bool Sweep, const FHitResult& Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shoot")
	USphereComponent* Project_Collis;//�������� �����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shoot")
	UStaticMeshComponent* Mesh;//������ ��������


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shoot")
	UProjectileMovementComponent* Project_Move;//����� �������� ���������

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shoot")
		float Projectil_Speed;//�������� ���������

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shoot")
		float Damage;//����
};
