
#include "Health_Component.h"
#include "GameFramework/Actor.h"

UHealth_Component::UHealth_Component():
	Health(100)
{
}

void UHealth_Component::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnTakeAnyDamage.AddDynamic(this,&UHealth_Component::OnOwnerDamaged);
}

void UHealth_Component::OnOwnerDamaged(AActor* DamageActor, float Damage, const UDamageType* DamageType, AController* Instigat, AActor* DamageCauser)
{
	ChangeHealth(-Damage);
}

void UHealth_Component::ChangeHealth(float Value)
{
	Health += Value;

	if (Health<=0.f)
	{
		GetOwner()->OnTakeAnyDamage.RemoveDynamic(this, &UHealth_Component::OnOwnerDamaged);
		OnHealthEnded.Broadcast();
	}
}

float UHealth_Component::GetHealth()
{
	return Health;
}


