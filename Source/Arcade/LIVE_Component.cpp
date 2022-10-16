
#include "LIVE_Component.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"


ULIVE_Component::ULIVE_Component():
	Health(3)
{
}

void ULIVE_Component::BeginPlay()
{
	Super::BeginPlay();

	APawn* PawnPlayer= UGameplayStatics::GetPlayerPawn(this, 0);
}

void ULIVE_Component::ChangeHealths(int ByValue)
{
	//int добавляется к жизням
	Health += ByValue;
	HealthsChanged.Broadcast(ByValue);
	if (Health<=0)
	{
		HealthsEnded.Broadcast();
	}
}

int ULIVE_Component::GetHealths()
{
	return Health;
}

