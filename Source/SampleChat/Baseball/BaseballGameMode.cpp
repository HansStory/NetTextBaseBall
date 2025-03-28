// Fill out your copyright notice in the Description page of Project Settings.


#include "Baseball/BaseballGameMode.h"
#include "Baseball/BaseballController.h"
#include "Baseball/BaseballPlayerState.h"

#include "Baseball/BaseballFunctionLibrary.h"

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

void ABaseballGameMode::PlayerReady(APlayerController* PlayerController)
{
	if (ReadyCount < AllPlayerControllers.Num())
	{
		ReadyCount++;

		SendMessageToAllClient(FString::Printf(TEXT("[%s] 준비완료!"), *PlayerController->PlayerState->GetPlayerName()));

		if (ReadyCount == AllPlayerControllers.Num())
		{
			GameStart();
		}
	}

}

void ABaseballGameMode::GameStart()
{
	CurrentGameState = EGameState::Playing;

	SendMessageToAllClient(FString::Printf(TEXT("게임을 시작합니다!")));
	GenerateRandomNum();
	SendMessageToAllClient(FString::Printf(TEXT("투수와 포수 사인을 주고 받습니다!")));
}

void ABaseballGameMode::GameEnd()
{
}

void ABaseballGameMode::RecieveMessageFromClient_Implementation(APlayerController* PlayerController, const FString& Message)
{
	FString PlayerName = *PlayerController->PlayerState->GetPlayerName();
	UE_LOG(LogTemp, Warning, TEXT("[Server] Received Message From : %s"), *PlayerName);

	FString FormattedString = FString::Printf(TEXT("[%s] %s"), *PlayerName, *Message);
	SendMessageToAllClient(FormattedString);

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

void ABaseballGameMode::SendMessageToAllClient(const FString& Message)
{
	for (auto PC : AllPlayerControllers)
	{
		PC->Client_ReceiveMessage(Message);
	}
}

void ABaseballGameMode::Multicast_BroadcastMessage_Implementation(const FString& Message)
{
	// 멀티캐스트 로직 변경해야 할것 같음
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
			UE_LOG(LogTemp, Warning, TEXT("[Server](%s) Try Change Player Name : %s -> %s"), *PlayerController->GetName(), *PS->GetPlayerName(), *NewName);
			PS->SetPlayerName(NewName);
		}
	}
}

void ABaseballGameMode::ReceiveAnswerFromClient(APlayerController* PlayerController, const FString& Answer)
{
	if (ABaseballController* BaseballPC = Cast<ABaseballController>(PlayerController))
	{
		ABaseballPlayerState* PS = PlayerController->GetPlayerState<ABaseballPlayerState>();
		if (PS)
		{
			PS->IncreseTryCount();
			FString Message = FString::Printf(TEXT("[%s]가 입력했습니다! (%d/3)"), *PS->GetPlayerName(), PS->GetTryCount());
			SendMessageToAllClient(Message);
		}

		FString Result = ValidateAndCheckGuess(Answer);
		SendMessageToClient(PlayerController, FString::Format(TEXT("결과는 !! : {0}"), { Result }));

		BaseballPC->Client_ReceiveAnswer(Answer);
	}
}


void ABaseballGameMode::GenerateRandomNum()
{
	ServerGenerateNum = UBaseballFunctionLibrary::GenerateRandomNum();

	UE_LOG(LogTemp, Error, TEXT("[Server] Generate RandomNum : %s"), *ServerGenerateNum);
}

FString ABaseballGameMode::ValidateAndCheckGuess(const FString& Input)
{
	return UBaseballFunctionLibrary::ValidateAndCheckInput(Input, ServerGenerateNum);
}