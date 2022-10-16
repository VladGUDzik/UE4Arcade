
#include "Bonus_Shoot.h"
#include "Kismet/GameplayStatics.h"
#include "ArcadeGameModeBase.h"

void ABonus_Shoot::BonusCollect_Implementation()
{
	AArcadeGameModeBase* Gamemode = Cast<AArcadeGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (!Gamemode) return;
	
	Gamemode->ChangeShootLevel(true);



	Super::BonusCollect_Implementation();
}