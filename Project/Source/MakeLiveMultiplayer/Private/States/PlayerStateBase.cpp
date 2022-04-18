// Built with ❤ by Make Live

#include "States/PlayerStateBase.h"
#include "AttributeSets/AttributeSetBase.h"
#include "Abilities/AbilitySystemComponentBase.h"

APlayerStateBase::APlayerStateBase()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponentBase>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSetBase = CreateDefaultSubobject<UAttributeSetBase>(TEXT("AttributeSetBase"));

	NetUpdateFrequency = 100.0f;

	DeadTag = FGameplayTag::RequestGameplayTag("State.Dead");
}

UAbilitySystemComponent* APlayerStateBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSetBase* APlayerStateBase::GetAttributeSetBase() const
{
	return AttributeSetBase;
}