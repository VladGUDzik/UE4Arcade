
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bonus.generated.h"

UCLASS(Blueprintable)
class ARCADE_API ABonus : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABonus();

	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
		class USoundBase* CollectedSound;
protected:

	virtual void NotifyActorBeginOverlap(AActor* OtherActor)override;//соприкосновение Actor'ов

	UFUNCTION(BlueprintNativeEvent)
	void BonusCollect();//бонусы присваиваются
	virtual void BonusCollect_Implementation();

	virtual void Tick(float DeltaTime)override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shoot")
	class USphereComponent* Collis;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Visual")
		UParticleSystem* CollectParticle;
};
