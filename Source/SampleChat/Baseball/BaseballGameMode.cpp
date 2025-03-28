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

		FString Result = ValidateAndCheckGuess(Answer, ServerGenerateNum);
		SendMessageToClient(PlayerController, FString::Format(TEXT("결과는 !! : {0}"), { Result }));

		BaseballPC->Client_ReceiveAnswer(Answer);
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

	UE_LOG(LogTemp, Error, TEXT("[Server] Generate RandomNum : %s"), *ServerGenerateNum);
}

FString ABaseballGameMode::ValidateAndCheckGuess(const FString& Input, const FString& SecretNumber)
{
	// 입력 검증
	if (!Input.StartsWith("/"))
	{
		return FString(TEXT("[Error] / 입력하지 않음 : OUT"));
	}

	FString Guess = Input.Mid(1); // '/' 이후의 문자열 추출

	if (Guess.Len() != 3)
	{
		return FString(TEXT("[Error] 입력 길이 초과 : OUT"));
	}
	else if (!Guess.IsNumeric())
	{
		return FString(TEXT("[Error] 숫자가 아님 : OUT"));
	}

	// 중복 숫자 검사
	TSet<TCHAR> UniqueDigits;
	for (TCHAR Digit : Guess)
	{
		if (Digit < '1' || Digit > '9' || UniqueDigits.Contains(Digit))
		{
			return FString(TEXT("[Error] 중복된 값 입력 : OUT"));
		}
		UniqueDigits.Add(Digit);
	}

	// 스트라이크 및 볼 개수 계산
	int32 Strikes = 0;
	int32 Balls = 0;

	for (int32 i = 0; i < 3; i++)
	{
		if (Guess[i] == SecretNumber[i])
		{
			Strikes++;
		}
		else if (SecretNumber.Contains(FString(1, &Guess[i])))
		{
			Balls++;
		}
	}

	// 결과 반환
	if (Strikes == 3)
	{
		return FString(TEXT("3S 0B ⇒ Win"));
	}
	else if (Strikes == 0 && Balls == 0)
	{
		return "OUT";
	}
	else
	{
		return FString::Printf(TEXT("%dS %dB"), Strikes, Balls);
	}
}