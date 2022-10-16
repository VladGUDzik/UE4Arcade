
#include "Arcade_GameInstance.h"

UArcade_GameInstance::UArcade_GameInstance()
{
	//LIVE_Component = CreateDefaultSubobject<ULIVE_Component>(TEXT("LIVE_Component"));
}

void UArcade_GameInstance::AddPoints(int Points)
{
	GamePoints += Points;
}
