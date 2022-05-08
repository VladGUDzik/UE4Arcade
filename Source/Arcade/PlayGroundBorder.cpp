
#include "PlayGroundBorder.h"
#include"Components/BoxComponent.h"
#include "Arcade/Ship.h"

APlayGroundBorder::APlayGroundBorder()
{
    Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));

    SetRootComponent(Trigger);
    Trigger->SetCollisionProfileName("OverlapAll");
}

void APlayGroundBorder::NotifyActorEndOverlap(AActor* OtherActor)
{
    Super::NotifyActorEndOverlap(OtherActor);

    if (!OtherActor)return;
    if (Cast<AShip>(OtherActor))return;

    OtherActor->Destroy();
}
