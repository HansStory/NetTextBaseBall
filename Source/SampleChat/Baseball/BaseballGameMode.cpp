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
		ABaseballPlayerState* BaseballPS = PlayerController->GetPlayerState<ABaseballPlayerState>();
		if (BaseballPS)
		{
			UE_LOG(LogTemp, Warning, TEXT("[Server](%s) Try Change Player Name : %s -> %s"), *PlayerController->GetName(), *BaseballPS->GetPlayerName(), *NewName);
			BaseballPS->SetPlayerName(NewName);
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

	for (ABaseballController* BaseballPC : AllPlayerControllers)
	{
		BaseballPC->Client_OnGameStart();
	}
}

void ABaseballGameMode::ReceiveAnswerFromClient(APlayerController* PlayerController, const FString& Answer)
{
	if (bGameEnded) return;
	if (CurrentGameState != EGameState::Playing) return;

	if (ABaseballController* BaseballPC = Cast<ABaseballController>(PlayerController))
	{
		ABaseballPlayerState* BaseballPS = PlayerController->GetPlayerState<ABaseballPlayerState>();
		if (BaseballPS)
		{
			BaseballPS->IncreseTryCount();
			FString Message = FString::Printf(TEXT("[%s]가 입력했습니다! (%d/3)"), *BaseballPS->GetPlayerName(), BaseballPS->GetTryCount());
			SendMessageToAllClient(Message);

			FString Result = UBaseballFunctionLibrary::ValidateAndCheckInput(Answer, ServerGenerateNum);
			SendMessageToClient(PlayerController, FString::Printf(TEXT("결과는 : %s"), *Result));

			if (Result.Contains("OUT"))
			{
				BaseballPS->SetOut(true);
				SendMessageToAllClient(FString::Printf(TEXT("[%s] 아웃되었습니다!"), *BaseballPS->GetPlayerName()));
			}
			else if (Result.Contains("3S"))
			{
				SendMessageToAllClient(FString::Printf(TEXT("[%s] 승리! 3스트라이크를 달성했습니다!"), *PlayerController->PlayerState->GetPlayerName()));
				GameEnd();
				return;
			}

		}

		BaseballPC->Client_ReceiveAnswer(Answer);

		// 게임 종료 조건 체크
		CheckGameEndCondition(BaseballPC);
	}
}

void ABaseballGameMode::CheckGameEndCondition(ABaseballController* CurrentPlayer)
{
	if (bGameEnded) return;

	int32 ActivePlayers = 0;
	ABaseballController* LastActivePlayer = nullptr;
	bool bAllPlayersFinished = true;

	// 모든 플레이어 상태 확인
	for (ABaseballController* PC : AllPlayerControllers)
	{
		ABaseballPlayerState* PS = PC->GetPlayerState<ABaseballPlayerState>();
		if (PS)
		{
			// 아직 시도 횟수가 남은 플레이어가 있는지 확인
			if (PS->GetTryCount() < 3)
			{
				bAllPlayersFinished = false;
			}

			// 아웃되지 않은 플레이어 수 확인
			if (!PS->IsOut())
			{
				ActivePlayers++;
				LastActivePlayer = PC;
			}
		}
	}

	// 승리 조건 1: 마지막 남은 플레이어
	if (ActivePlayers == 1 && AllPlayerControllers.Num() > 1)
	{
		FString WinnerName = LastActivePlayer->PlayerState->GetPlayerName();
		SendMessageToAllClient(FString::Printf(TEXT("[%s] 승리! 다른 플레이어들이 모두 아웃되었습니다!"), *WinnerName));
		GameEnd();
		return;
	}

	// 승리 조건 2: 모든 플레이어가 3번 시도했고 승자가 없으면 무승부
	if (bAllPlayersFinished && !bGameEnded)
	{
		SendMessageToAllClient(TEXT("무승부! 모든 플레이어가 3번의 시도를 마쳤지만 승자가 없습니다."));
		GameEnd();
	}
}

void ABaseballGameMode::GameEnd()
{
	CurrentGameState = EGameState::GameOver;
	bGameEnded = true;

	for (ABaseballController* BaseballPC : AllPlayerControllers)
	{
		BaseballPC->Client_OnGameEnd();
	}

	// 3초 후 게임 리셋
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_ResetGame, this, &ABaseballGameMode::ResetGame, 3.0f, false);
}

void ABaseballGameMode::ResetGame()
{
	// 게임 상태 초기화
	CurrentGameState = EGameState::Waiting;
	bGameEnded = false;
	ReadyCount = 0;
	ServerGenerateNum = "";

	// 플레이어 상태 초기화
	for (ABaseballController* BaseballPC : AllPlayerControllers)
	{
		ABaseballPlayerState* BaseballPS = BaseballPC->GetPlayerState<ABaseballPlayerState>();
		if (BaseballPS)
		{
			BaseballPS->Reset();
		}

		BaseballPC->Client_OnGameReset();
	}

	SendMessageToAllClient(TEXT("게임이 리셋되었습니다. 준비 버튼을 눌러 새 게임을 시작하세요!"));
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