#pragma once

#include "CoreMinimal.h"
#include "Bonus.h"
#include "BonusPoints.generated.h"

UCLASS()
class ARCADE_API ABonusPoints : public ABonus
{
	GENERATED_BODY()

protected:
	virtual void BonusCollect_Implementation()override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bonus")
		int Points;
};
