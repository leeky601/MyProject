// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "MyAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class UMyAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:

	void ApplyInitialEffect();

private:

	UPROPERTY(EditDefaultsOnly, Category = "GameplayEffect")
	TArray<TSubclassOf<UGameplayEffect>> EffectsToGive;
};
