
#pragma once

#include "CoreMinimal.h"
#include "Bonus.h"
#include "Bonus_Shoot.generated.h"

UCLASS()
class ARCADE_API ABonus_Shoot : public ABonus
{
	GENERATED_BODY()
protected:
	virtual void BonusCollect_Implementation()override;

};
