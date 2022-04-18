// Built with ❤ by Make Live

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "CharacterBase.generated.h"

UCLASS(config=Game)
class MAKELIVEMULTIPLAYER_API ACharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ACharacterBase();

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UFUNCTION(BlueprintCallable)
	virtual int32 GetAbilityLevel(EAbilityInputID AbilityID) const;

	UFUNCTION(BlueprintCallable)
	int32 GetCharacterLevel() const;

	UFUNCTION(BlueprintCallable)
	float GetMaxHealth() const;

protected:
	FGameplayTag DeadTag;

	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY()
	class UAbilitySystemComponentBase* AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<class UGameplayAbilityBase>> CharacterAbilities;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
	TSubclassOf<class UGameplayEffect> DefaultAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<class UGameplayEffect>> StartupEffects;

	UPROPERTY()
	class UAttributeSetBase* AttributeSetBase;

	virtual void AddCharacterAbilities();

	virtual void InitializeAttributes();

	virtual void AddStartupEffects();

	virtual void OnRep_PlayerState() override;

	virtual void PossessedBy(AController* NewController) override;

	virtual void SetHealth(float Health);

	void MoveForward(float Value);

	void MoveRight(float Value);

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);

	bool ASCInputBound = false;

	void BindASCInput();
};