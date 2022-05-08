
#include "Bonus_SHIELD.h"
#include "Kismet/GameplayStatics.h"
#include "Arcade/Ship.h"
#include "Engine/World.h"
#include "Arcade/Ship_Shield.h"
#include "ArcadeGameModeBase.h"

void ABonus_SHIELD::BonusCollect_Implementation()
{
	APawn* Pawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (!Pawn)return;
	AShip* Ship = Cast<AShip>(Pawn);

	if (!Ship)return;
	//спаунится бонус
	AShip_Shield* Ship_Shield = GetWorld()->SpawnActor<AShip_Shield>(ShieldClass);

	AArcadeGameModeBase* Gamemode = Cast<AArcadeGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (Gamemode)
	{
		Gamemode->AddHealth(1);
	}
	//активируем щит
	Ship_Shield->ActivateShield(Ship);
	Super::BonusCollect_Implementation();
}