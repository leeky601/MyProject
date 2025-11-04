// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MyPlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

AMyPlayerCharacter::AMyPlayerCharacter()
{
	bUseControllerRotationPitch = false;    //컨트롤러와 폰의 회전 값을 동기화
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->bUsePawnControlRotation = true;  //카메라 붐이 컨트롤러의 회전을 따라옴

	FollowCam = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCam"));
	FollowCam->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCam->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = false; //캐릭터의 벡터가 폰을 회전시키지 않음
	GetCharacterMovement()->bUseControllerDesiredRotation = true; // 캐릭터의 rot 값을 컨트롤러의 rot 값으로 roationrate 속도로 동기화
	GetCharacterMovement()->RotationRate = FRotator(0.f, 720.f, 0.f);

}

void AMyPlayerCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();

	UEnhancedInputLocalPlayerSubsystem* SubSystem = GetController<APlayerController>()->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

	check(SubSystem);

	SubSystem->RemoveMappingContext(DefaultMappingContext);
	SubSystem->AddMappingContext(DefaultMappingContext, 0);
}

void AMyPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ThisClass::Jump);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::Input_Look);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
	}
}

void AMyPlayerCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D InputVal = InputActionValue.Get<FVector2D>();

	AddControllerYawInput(InputVal.X);

	AddControllerPitchInput(-InputVal.Y);
}

void AMyPlayerCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputVal = InputActionValue.Get<FVector2D>();
	const FVector2D InputValNormal = InputVal.GetSafeNormal();

	AddMovementInput(GetMoveFwdVector() * InputValNormal.Y + GetCamRightVector() * InputValNormal.X);
}

const FVector AMyPlayerCharacter::GetCamFwdVector()
{
	return FollowCam->GetForwardVector();
}

const FVector AMyPlayerCharacter::GetCamRightVector()
{
	return FollowCam->GetRightVector();
}

const FVector AMyPlayerCharacter::GetMoveFwdVector()
{
	return FVector::CrossProduct(GetCamRightVector(), FVector::UpVector);
}


