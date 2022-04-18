// Built with ❤ by Make Live

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "PlayerStateBase.generated.h"

UCLASS()
class MAKELIVEMULTIPLAYER_API APlayerStateBase : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	APlayerStateBase();

	class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	class UAttributeSetBase* GetAttributeSetBase() const;

protected:
	FGameplayTag DeadTag;

	UPROPERTY()
	class UAbilitySystemComponentBase* AbilitySystemComponent;

	UPROPERTY()
	class UAttributeSetBase* AttributeSetBase;

};
