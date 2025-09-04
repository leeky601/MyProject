// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/MyCharacter.h"
#include "MyPlayerCharacter.generated.h"

struct FInputActionValue;

UCLASS()
class AMyPlayerCharacter : public AMyCharacter
{
	GENERATED_BODY()
	
public:
	AMyPlayerCharacter();

protected:
	virtual void PawnClientRestart() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Camera")
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleDefaultsOnly, Category = "Camera")
	class UCameraComponent* FollowCam ;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputMappingContext* DefaultMappingContext ;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* JumpAction ;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* MoveAction;

	void Input_Look(const FInputActionValue& InputActionValue);
	void Input_Move(const FInputActionValue& InputActionValue);

	const FVector GetCamFwdVector();
	const FVector GetCamRightVector();
	const FVector GetMoveFwdVector();

};
