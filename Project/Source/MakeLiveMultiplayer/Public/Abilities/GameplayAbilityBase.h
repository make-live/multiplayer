// Built with ❤ by Make Live

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "MakeLiveMultiplayer/MakeLiveMultiplayer.h"
#include "GameplayAbilityBase.generated.h"


UCLASS()
class MAKELIVEMULTIPLAYER_API UGameplayAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UGameplayAbilityBase();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	EAbilityInputID AbilityInputID = EAbilityInputID::None;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	EAbilityInputID AbilityID = EAbilityInputID::None;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability")
	bool bActivateAbilityOnGranted;

	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
};
