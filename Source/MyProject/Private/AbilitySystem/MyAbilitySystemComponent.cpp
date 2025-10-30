// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/MyAbilitySystemComponent.h"

void UMyAbilitySystemComponent::ApplyInitialEffect()
{
	if (!GetOwner() || !GetOwner()->HasAuthority())
		return;

	for (const TSubclassOf< UGameplayEffect >& EffectClass: EffectsToGive)
	{
		FGameplayEffectSpecHandle GESpecHandle = MakeOutgoingSpec(EffectClass, 1, MakeEffectContext());
		ApplyGameplayEffectSpecToSelf(*GESpecHandle.Data);
	}
}
