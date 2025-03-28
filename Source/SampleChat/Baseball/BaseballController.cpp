#include "Baseball/BaseballController.h"

#include "Baseball/Widgets/BaseballWidget.h"
#include "Baseball/Widgets/EntryWidget.h"
#include "Baseball/Widgets/MainWidget.h"
#include "Baseball/Widgets/ResultWidget.h"

#include "Baseball/BaseballGameMode.h"
#include "Baseball/BaseballGameState.h"
#include "Baseball/BaseballPlayerState.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"


void ABaseballController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;
	SetInputMode(FInputModeUIOnly());

	if (IsLocalController())
	{
		if (IsValid(BaseballWidgetClass))
		{
			BaseballWidgetInstance = CreateWidget<UBaseballWidget>(this, BaseballWidgetClass);
			if (BaseballWidgetInstance)
			{
				BaseballWidgetInstance->AddToViewport();
				//BaseballWidgetInstance->SetOwningPlayer(this);
			}
		}
	}
}

// 사용하지 않음
void ABaseballController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	ABaseballPlayerState* BaseballPS = GetPlayerState<ABaseballPlayerState>();
	if (IsValid(BaseballPS))
	{
		SetPlayerName(BaseballPS->GetPlayerName());
		//BaseballWidgetInstance->SetPlayerNameText(BaseballPS->GetPlayerName());
	}
}

void ABaseballController::Server_SendMessage_Implementation(const FString& Message)
{
	UE_LOG(LogTemp, Warning, TEXT("Server_SendMessage : %s"), *Message);

	ABaseballGameMode* BasballGM = GetWorld()->GetAuthGameMode<ABaseballGameMode>();
	if (BasballGM)
	{
		BasballGM->RecieveMessageFromClient(this, Message);
	}
}

void ABaseballController::Server_SetPlayerName_Implementation(const FString& Message)
{
	UE_LOG(LogTemp, Warning, TEXT("Server_SetPlayerName : %s"), *Message);
	ABaseballGameMode* BasballGM = GetWorld()->GetAuthGameMode<ABaseballGameMode>();
	if (BasballGM)
	{
		BasballGM->SetPlayerNickname(this, Message);
	}
}

void ABaseballController::Server_SendAnswer_Implementation(const FString& Answer)
{
	UE_LOG(LogTemp, Warning, TEXT("[%s] Server_SendAnswer : %s"), *PlayerState->GetPlayerName(), *Answer);

	ABaseballGameMode* BasballGM = GetWorld()->GetAuthGameMode<ABaseballGameMode>();
	if (BasballGM)
	{
		BasballGM->ReceiveAnswerFromClient(this, Answer);
	}
}

void ABaseballController::Server_PlayerReady_Implementation()
{
	ABaseballGameMode* BasballGM = GetWorld()->GetAuthGameMode<ABaseballGameMode>();
	if (BasballGM)
	{
		BasballGM->PlayerReady(this);
	}
}

void ABaseballController::Client_ReceiveMessage_Implementation(const FString& Message)
{
	UE_LOG(LogTemp, Log, TEXT("[%s] Client Receive Message : %s"), *PlayerState->GetPlayerName(), *Message);
	if (IsValid(GEngine))
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, Message);
	}
}

void ABaseballController::Client_ReceiveAnswer_Implementation(const FString& Answer)
{
	//UE_LOG(LogTemp, Warning, TEXT("[%s] Client Receive Answer : %s"), *PlayerState->GetPlayerName(), *Answer);

}

void ABaseballController::Client_OnGameStart_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("[%s] OnGameStart"), *PlayerState->GetPlayerName());

	if (IsValid(BaseballWidgetInstance))
	{
		BaseballWidgetInstance->OnGameStart();
	}
}

void ABaseballController::Client_OnGameEnd_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("[%s] OnGameEnd"), *PlayerState->GetPlayerName());

}

void ABaseballController::Client_OnGameReset_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("[%s] OnGameReset"), *PlayerState->GetPlayerName());

	if (IsValid(BaseballWidgetInstance))
	{
		BaseballWidgetInstance->OnGameReset();
	}
}

void ABaseballController::SetPlayerName(const FString& PlayerName)
{
	if (IsValid(BaseballWidgetInstance))
	{
		BaseballWidgetInstance->SetPlayerNameText(PlayerName);
	}
}


