
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayGroundBorder.generated.h"

UCLASS()
class ARCADE_API APlayGroundBorder : public AActor
{
	GENERATED_BODY()
	
public:	
	APlayGroundBorder();
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	class UBoxComponent * Trigger;

	virtual void NotifyActorEndOverlap(AActor* OtherActor)override;

};
