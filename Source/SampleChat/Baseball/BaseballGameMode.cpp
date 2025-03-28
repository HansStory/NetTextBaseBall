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

void ABaseballGameMode::SetPlayerNickname(APlayerController* PlayerController, const FString& NewName)
{
	if (PlayerController)
	{
		ABaseballPlayerState* PS = PlayerController->GetPlayerState<ABaseballPlayerState>();
		if (PS)
		{
			PS->SetPlayerName(NewName);
			UE_LOG(LogTemp, Log, TEXT("Player %s changed nickname to: %s"), *PlayerController->GetName(), *NewName);
		}
	}
}
