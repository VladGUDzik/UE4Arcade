
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Health_Component.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHealthEndedEvent);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ARCADE_API UHealth_Component : public UActorComponent
{
	GENERATED_BODY()

public:
	UHealth_Component();

protected:
	
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Health")
	float Health;

	UFUNCTION()
		void OnOwnerDamaged(AActor * DamageActor,float Damage,const UDamageType* DamageType,AController* Instigat,AActor* DamageCauser);

public:

	UFUNCTION(BlueprintCallable, Category = "Health")
		void ChangeHealth(float Value);

	UFUNCTION(BlueprintPure, Category = "Health")
		float GetHealth();

	UPROPERTY(BlueprintAssignable, Category = "Health")
		FHealthEndedEvent OnHealthEnded;
};
