// Built with ❤ by Make Live

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemComponentBase.generated.h"


UCLASS()
class MAKELIVEMULTIPLAYER_API UAbilitySystemComponentBase : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	bool bCharacterAbilitiesGiven = false;

	bool bStartupEffectsApplied = false;
};
