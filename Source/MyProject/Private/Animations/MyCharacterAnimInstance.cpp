// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/MyCharacterAnimInstance.h"
#include "Character/MyCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KismetAnimationLibrary.h"

void UMyCharacterAnimInstance::NativeInitializeAnimation()
{
	OwningCharacter = Cast<AMyCharacter>(TryGetPawnOwner());
	
	if (OwningCharacter)
	{
		OwningMovementComponent = OwningCharacter->GetCharacterMovement();
	}
}

void UMyCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (!OwningMovementComponent || !OwningCharacter)
	{
		return;
	}

	//lean 값 계산
	Speed = OwningCharacter->GetVelocity().Length();

	FRotator BodyRot = OwningCharacter->GetActorRotation();
	FRotator BodyRotDelta = UKismetMathLibrary::NormalizedDeltaRotator(BodyRot, BodyPrevRot);
	BodyPrevRot = BodyRot;

	YawSpeed = BodyRotDelta.Yaw / DeltaSeconds;

	SmoothedYawSpeed = UKismetMathLibrary::FInterpTo(SmoothedYawSpeed, YawSpeed, DeltaSeconds, SmoothedYawInterpSpeed);

	//점프
	bIsJumping = OwningMovementComponent->IsFalling();

	//lookoffset값 계산
	FRotator ControlRot = OwningCharacter->GetBaseAimRotation();
	LookRotOffset = UKismetMathLibrary::NormalizedDeltaRotator(ControlRot, BodyRot);

	//Direction
	LocomotionDirection = UKismetAnimationLibrary::CalculateDirection(OwningCharacter->GetVelocity(), OwningCharacter->GetActorRotation());

}

void UMyCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
}
