// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MyPlayerController.h"
#include "Kismet/GameplayStatics.h"

AMyGameModeBase::AMyGameModeBase()
{
}

void AMyGameModeBase::GotMessageFromClient_Implementation(APlayerController* PlayerController, const FString& Message)
{

	if (AMyPlayerController* ChatPC = Cast<AMyPlayerController>(PlayerController))
	{
		ChatPC->ReceiveMessageFromServer(Message);
	}

}

bool AMyGameModeBase::GotMessageFromClient_Validate(APlayerController* PlayerController, const FString& Message)
{
	UE_LOG(LogTemp, Warning, TEXT("[Server][GotMessageFromClient_Validate][%s]"), *Message);
	return true;
}