
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LIVE_Component.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHealthsEndedEvent);//���������� ��������� ��� ����� �����
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealthsChangedEvent,int,ChangeValue);//��������� ������


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARCADE_API ULIVE_Component : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	ULIVE_Component();

protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "LIVES")
	int Health;//�������
	
public:	

	UFUNCTION(BlueprintCallable, Category = "LIVES")
		void ChangeHealths(int ByValue);//��������� ������

	UFUNCTION(BlueprintPure, Category = "LIVES")
		int GetHealths();//��������� ������

	UPROPERTY(BlueprintAssignable, Category = "LIVES")
		FHealthsEndedEvent HealthsEnded;

	UPROPERTY(BlueprintAssignable, Category = "LIVES")
		FHealthsChangedEvent HealthsChanged;

};
