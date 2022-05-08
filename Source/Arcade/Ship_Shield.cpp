
#include "Ship_Shield.h"
#include "Arcade/Ship.h"
#include "Engine/World.h"
#include "TimerManager.h"

AShip_Shield::AShip_Shield():
	ShieldTime(5.f)
{

}

void AShip_Shield::ActivateShield(AShip* Ship)
{
	if (!Ship) 
	{
		Destroy();
		return;
	}
	ShieldforShip = Ship;
	ShieldforShip->bCanBeDamaged = false;

	FAttachmentTransformRules AttachRules= FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld,false);
	AttachToActor(Ship, AttachRules);

	GetWorld()->GetTimerManager().SetTimer(ShieldTimer,this,&AShip_Shield::DeactivateShield, ShieldTime, false);

}

void AShip_Shield::DeactivateShield()
{
	if (!ShieldforShip)return;
	ShieldforShip->bCanBeDamaged = true;
	Destroy();
}
