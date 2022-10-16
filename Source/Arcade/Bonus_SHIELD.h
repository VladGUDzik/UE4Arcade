
#pragma once

#include "CoreMinimal.h"
#include "Bonus.h"
#include "Bonus_SHIELD.generated.h"

class AShip_Shield;

UCLASS()
class ARCADE_API ABonus_SHIELD : public ABonus
{
	GENERATED_BODY()
protected:
	virtual void BonusCollect_Implementation()override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shield")
	TSubclassOf<AShip_Shield>ShieldClass;//массив из обектов самописного класса

};
