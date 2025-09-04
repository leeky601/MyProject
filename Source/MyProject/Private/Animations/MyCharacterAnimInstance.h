// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UMyCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	// the below functions are the native overrides for each phase
	// Native initialization override point
	virtual void NativeInitializeAnimation() override;
	// Native update override point. It is usually a good idea to simply gather data in this step and 
	// for the bulk of the work to be done in NativeThreadSafeUpdateAnimation.
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	// Native thread safe update override point. Executed on a worker thread just prior to graph update 
	// for linked anim instances, only called when the hosting node(s) are relevant
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	FORCEINLINE float GetSpeed() const {return Speed;}

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	FORCEINLINE bool IsMoving() const {return Speed != 0;}

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	FORCEINLINE float GetSmoothedYawSpeed() const { return SmoothedYawSpeed; }

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	FORCEINLINE bool GetIsJumping() const { return bIsJumping; }

	UPROPERTY()
	class AMyCharacter* OwningCharacter;

	UPROPERTY()
	class UCharacterMovementComponent* OwningMovementComponent ;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	float SmoothedYawInterpSpeed =1.f;

	float Speed;
	float YawSpeed;
	float SmoothedYawSpeed;
	bool bIsJumping;

	FRotator BodyPrevRot;
};