// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/MyPlayerController.h"
#include "Character/MyCharacter.h"

void AMyPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AMyCharacter* MyCharacter = Cast<AMyCharacter>(InPawn);
	if (MyCharacter)
	{
		MyCharacter->ServerSideInit();
	}
}

void AMyPlayerController::AcknowledgePossession(APawn* InPawn)
{
	Super::AcknowledgePossession(InPawn);

	AMyCharacter* MyCharacter = Cast<AMyCharacter>(InPawn);
	if (MyCharacter)
	{
		MyCharacter->ClientSideInit();
	}
}
