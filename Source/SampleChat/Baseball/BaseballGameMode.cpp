// Fill out your copyright notice in the Description page of Project Settings.


#include "Baseball/BaseballGameMode.h"
#include "Baseball/BaseballController.h"
#include "Baseball/BaseballPlayerState.h"

ABaseballGameMode::ABaseballGameMode()
{

}

void ABaseballGameMode::BeginPlay()
{
	Super::BeginPlay();

}

void ABaseballGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	ABaseballController* BaseballPC = Cast<ABaseballController>(NewPlayer);
	if (IsValid(BaseballPC))
	{
		AllPlayerControllers.Add(BaseballPC);

		ABaseballPlayerState* BaseballPS = BaseballPC->GetPlayerState<ABaseballPlayerState>();
		if (IsValid(BaseballPS))
		{
			BaseballPS->SetPlayerName(TEXT("Player") + FString::FromInt(AllPlayerControllers.Num()));

		}

	}

}


void ABaseballGameMode::GenerateRandomNum()
{
	constexpr int32 NumLength = 3;
	FString RandomNumber;
	const FRandomStream RandStream(FDateTime::Now().GetTicks());

	while (RandomNumber.Len() < NumLength)
	{
		int32 RandNumber = RandStream.RandRange(1, 9);

		if (!RandomNumber.Contains(FString::FromInt(RandNumber)))
		{
			RandomNumber += FString::FromInt(RandNumber);
		}
	}

	ServerGenerateNum = RandomNumber;
}

void ABaseballGameMode::RecieveMessageFromClient_Implementation(APlayerController* PlayerController, const FString& Message)
{
	FString PlayerName = *PlayerController->PlayerState->GetPlayerName();
	UE_LOG(LogTemp, Warning, TEXT("[Server] Received Message From : %s"), *PlayerName);

	FString FormattedString = FString::Printf(TEXT("[%s] %s"), *PlayerName, *Message);
	Multicast_BroadcastMessage(FormattedString);

	//SendMessageToClient(PlayerController, Message);
}

bool ABaseballGameMode::RecieveMessageFromClient_Validate(APlayerController* PlayerController, const FString& Message)
{
	return true;
}

void ABaseballGameMode::SendMessageToClient(APlayerController* PlayerController, const FString& Message)
{
	if (ABaseballController* BaseballPC = Cast<ABaseballController>(PlayerController))
	{
		BaseballPC->Client_ReceiveMessage(Message);
	}
}

void ABaseballGameMode::Multicast_BroadcastMessage_Implementation(const FString& Message)
{
	for (auto PC : AllPlayerControllers)
	{
		PC->Client_ReceiveMessage(Message);
	}
}


void ABaseballGameMode::SetPlayerNickname(APlayerController* PlayerController, const FString& NewName)
{
	if (PlayerController)
	{
		ABaseballPlayerState* PS = PlayerController->GetPlayerState<ABaseballPlayerState>();
		if (PS)
		{
			UE_LOG(LogTemp, Log, TEXT("[Server] %s Try Change Player Name to:%s"), *PlayerController->GetName(), *NewName);
			PS->SetPlayerName(NewName);
		}

		//ABaseballController* BaseballPC = Cast<ABaseballController>(PlayerController);
		//if (BaseballPC)
		//{
		//	BaseballPC->Client_ShowMainWidget();
		//}
	}
}
