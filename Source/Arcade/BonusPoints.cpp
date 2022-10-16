
#include "BonusPoints.h"
#include "Kismet/GameplayStatics.h"
#include "Arcade_GameInstance.h"

void ABonusPoints::BonusCollect_Implementation()
{
	UArcade_GameInstance* GameInstanse = Cast<UArcade_GameInstance>(UGameplayStatics::GetGameInstance(this));
	if (GameInstanse)
	{
		GameInstanse->AddPoints(Points);
	}

	Super::BonusCollect_Implementation();
}