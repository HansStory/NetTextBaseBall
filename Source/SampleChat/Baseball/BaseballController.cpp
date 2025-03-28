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

		// EntryWidget 생성 및 표시
		//EntryWidgetInstance = CreateWidget<UEntryWidget>(this, EntryWidgetClass);
		//if (EntryWidgetInstance)
		//{
		//	EntryWidgetInstance->AddToViewport();
		//}

		//MainWidgetInstance = CreateWidget<UMainWidget>(this, MainWidgetClass);
		//if (MainWidgetInstance)
		//{
		//	EntryWidgetInstance->AddToViewport();
		//}
	}
}

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


//void ABaseballController::ShowEntryWidget()
//{
//}
//
//void ABaseballController::ShowMainWidget()
//{
//	if (!IsLocalPlayerController()) return;
//
//	if (EntryWidgetInstance)
//	{
//		EntryWidgetInstance->RemoveFromParent();
//		EntryWidgetInstance = nullptr;
//	}
//
//	if (IsValid(MainWidgetClass))
//	{
//		MainWidgetInstance = CreateWidget<UMainWidget>(this, MainWidgetClass);
//		if (MainWidgetInstance)
//		{
//			MainWidgetInstance->AddToViewport();
//		}
//	}
//}

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
	UE_LOG(LogTemp, Warning, TEXT("[%s] Client Receive Message : %s"), *PlayerState->GetPlayerName(), *Message);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, Message);
	}
}

void ABaseballController::Client_ReceiveAnswer_Implementation(const FString& Answer)
{
	UE_LOG(LogTemp, Warning, TEXT("[%s] Client Receive Answer : %s"), *PlayerState->GetPlayerName(), *Answer);

}


void ABaseballController::SetPlayerName(const FString& PlayerName)
{
	if (IsValid(BaseballWidgetInstance))
	{
		BaseballWidgetInstance->SetPlayerNameText(PlayerName);
		//ABaseballPlayerState* BaseballPS = GetPlayerState<ABaseballPlayerState>();
		//if (IsValid(BaseballPS))
		//{
		//	BaseballWidgetInstance->SetPlayerNameText(BaseballPS->GetPlayerName());
		//}
	}

	//if (IsValid(MainWidgetInstance))
	//{
	//	MainWidgetInstance->SetPlayerNameText(PlayerName);
	//}
}

























//void ABaseballController::Client_ShowMainWidget_Implementation()
//{
//	if (!IsLocalPlayerController()) return;
//
//	if (EntryWidgetInstance)
//	{
//		EntryWidgetInstance->RemoveFromParent();
//		EntryWidgetInstance = nullptr;
//	}
//
//	if (IsValid(MainWidgetClass))
//	{
//		MainWidgetInstance = CreateWidget<UMainWidget>(this, MainWidgetClass);
//		if (MainWidgetInstance)
//		{
//			MainWidgetInstance->AddToViewport();
//
//			AGameStateBase* GameState = GetWorld()->GetGameState();
//			if (GameState)
//			{
//				TArray<ABaseballPlayerState*> PlayerStates;
//
//				for (APlayerState* PS : GameState->PlayerArray)
//				{
//					ABaseballPlayerState* BaseballPS = Cast<ABaseballPlayerState>(PS);
//					if (BaseballPS)
//					{
//						PlayerStates.Add(BaseballPS);
//						//BaseballPS->OnPlayerNameChanged.AddDynamic(this, &AMyPlayerController::HandleOtherPlayerNameChanged);
//					}
//				}
//
//				MainWidgetInstance->InitMainWidget(PlayerStates);
//			}
//
//		}
//	}
//}

//
//
//void ABaseballController::Client_UpdateOtherPlayerName_Implementation(int32 Index, const FString& OtherPlayerName) const
//{
//	if (MainWidgetInstance)
//	{
//		//MainWidgetInstance->SetPlayerName(Index, OtherPlayerName);
//	}
//}
//


//void ABaseballController::Server_JoinGame_Implementation(const FString& NewPlayerName)
//{
//	if (ABaseballGameState* BaseballGS = Cast<ABaseballGameState>(GetWorld()->GetGameState()))
//	{
//		if (ABaseballPlayerState* BaseballPS = Cast<ABaseballPlayerState>(PlayerState))
//		{
//			// TO DO : 
//			//BaseballGS->JoinGame(BaseballPS, NewPlayerName);
//		}
//	}
//}
//
//
//bool ABaseballController::Server_JoinGame_Validate(const FString& NewPlayerName)
//{
//	return true;
//}
//
//void ABaseballController::Client_JoinGame_Implementation(bool bIsHost)
//{
//	if (EntryWidgetInstance->IsInViewport())
//	{
//		EntryWidgetInstance->RemoveFromParent();
//	}
//
//	if (MainWidgetInstance)
//	{
//		MainWidgetInstance->AddToViewport();
//
//		//MainWidgetInstance->SetPlayerName(0, PlayerState->GetPlayerName());
//	}
//}


//void ABaseballController::SendMessageToServer_Implementation(const FString& Message)
//{
//	UE_LOG(LogTemp, Log, TEXT("[Server] RPC from client : %s"), *Message);
//
//	ABaseballGameMode* GameMode = Cast<ABaseballGameMode>(GetWorld()->GetAuthGameMode());
//	if (GameMode)
//	{
//		GameMode->GotMessageFromClient(this, Message);
//	}
//}
//
//void ABaseballController::ReceiveMessageFromServer_Implementation(const FString& Message)
//{
//	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, Message);
//}

// Message
//void ABaseballController::SendMessageToServer_Implementation(const FString& Message)
//{
//	UE_LOG(LogTemp, Log, TEXT("[Server] RPC from client : %s"), *Message);
//
//	//AMyGameModeBase* GameMode = Cast<AMyGameModeBase>(GetWorld()->GetAuthGameMode());
//	//if (GameMode)
//	//{
//	//	GameMode->GotMessageFromClient(this, Message);
//	//}
//}

//void ABaseballController::ReceiveMessageFromServer_Implementation(const FString& Message)
//{
//	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, Message);
//}

//void ABaseballController::InitWidget()
//{
//	if (IsLocalController())
//	{
//		if (EntryWidgetClass && EntryWidgetInstance == nullptr)
//		{
//			EntryWidgetInstance = CreateWidget<UEntryWidget>(this, EntryWidgetClass);
//			if (EntryWidgetInstance)
//			{
//				EntryWidgetInstance->AddToViewport();
//				EntryWidgetInstance->SetOwningPlayer(this);
//				//EntryWidgetInstance->OnConfirmButtonClicked.AddDynamic(this, &ABaseballController::OnConfirmButtonClicked);
//			}
//		}
//
//	}
//
//	if (HasAuthority())
//	{
//		EntryWidgetInstance->SetOwningPlayer(this);
//	}
//	else
//	{
//		EntryWidgetInstance->SetOwningPlayer(this);
//	}
//
//}
//
//void ABaseballController::ShowEntryWidget()
//{
//	if (EntryWidgetInstance)
//	{
//		EntryWidgetInstance->AddToViewport();
//	}
//
//	if (MainWidgetInstance)
//	{
//		if (MainWidgetInstance->bIsEnabled)
//		{
//			MainWidgetInstance->RemoveFromParent();
//		}
//	}
//
//	if (ResultWidgetInstance)
//	{
//		if (ResultWidgetInstance->bIsEnabled)
//		{
//			ResultWidgetInstance->RemoveFromParent();
//		}
//	}
//}
//
//void ABaseballController::ShowMainWidget()
//{
//	if (EntryWidgetInstance)
//	{
//		if (EntryWidgetInstance->bIsEnabled)
//		{
//			EntryWidgetInstance->RemoveFromParent();
//		}
//	}
//
//	if (MainWidgetInstance)
//	{
//		MainWidgetInstance->AddToViewport();
//	}
//
//	if (ResultWidgetInstance)
//	{
//		if (ResultWidgetInstance->bIsEnabled)
//		{
//			ResultWidgetInstance->RemoveFromParent();
//		}
//	}
//}
//
//void ABaseballController::ShowResultWidget()
//{
//	if (EntryWidgetInstance)
//	{
//		if (EntryWidgetInstance->bIsEnabled)
//		{
//			EntryWidgetInstance->RemoveFromParent();
//		}
//	}
//
//	if (MainWidgetInstance)
//	{
//		if (MainWidgetInstance->bIsEnabled)
//		{
//			MainWidgetInstance->RemoveFromParent();
//		}
//	}
//
//	if (ResultWidgetInstance)
//	{
//		ResultWidgetInstance->AddToViewport();
//	}
//}
//
//FText ABaseballController::GetUserId()
//{
//	return userId;
//}
//
//void ABaseballController::SetUserId(FText textUserId)
//{
//	userId = textUserId;
//}
//
//void ABaseballController::OnConfirmButtonClicked(const FString& PlayerName)
//{
//	PlayerNickname = PlayerName;
//
//	// 서버에서 모든 플레이어 정보 로깅
//	int32 PlayerIndex = 0;
//	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
//	{
//		ABaseballController* PC = Cast<ABaseballController>(It->Get());
//		if (PC)
//		{
//			FString PlayerRole = PC->IsLocalController() ? TEXT("Local") : TEXT("Remote");
//			UE_LOG(LogTemp, Log, TEXT("[Server] Player %d - %s (Nickname: %s)"),
//				PlayerIndex, *PlayerRole, *PC->PlayerNickname);
//			PlayerIndex++;
//		}
//	}
//	if (HasAuthority())
//	{
//		//int32 PlayerIndex = 0;
//		//for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
//		//{
//		//	ABaseballController* PC = Cast<ABaseballController>(It->Get());
//		//	if (PC)
//		//	{
//		//		FString PlayerRole = PC->IsLocalController() ? TEXT("Local") : TEXT("Remote");
//		//		UE_LOG(LogTemp, Log, TEXT("[Server] Player %d - %s (Nickname: %s)"),
//		//			PlayerIndex, *PlayerRole, *PC->PlayerNickname);
//		//		PlayerIndex++;
//		//	}
//		//}
//	}
//	else
//	{
//
//	}
//
//	// 로컬 플레이어인 경우에만 UI 업데이트
//	//if (IsLocalController())
//	//{
//	//	// EntryWidget 제거
//	//	if (EntryWidgetInstance)
//	//	{
//	//		EntryWidgetInstance->RemoveFromParent();
//	//		EntryWidgetInstance = nullptr;
//	//	}
//
//	//	// MainWidget 생성
//	//	if (MainWidgetClass)
//	//	{
//	//		MainWidgetInstance = CreateWidget<UMainWidget>(this, MainWidgetClass);
//	//		if (MainWidgetInstance)
//	//		{
//	//			MainWidgetInstance->AddToViewport();
//
//	//			// 클라이언트에서는 자신의 정보만 표시
//	//			int32 LocalPlayerIndex = 0;
//	//			if (GetWorld())
//	//			{
//	//				int32 Index = 0;
//	//				for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
//	//				{
//	//					if (It->Get() == this)
//	//					{
//	//						LocalPlayerIndex = Index;
//	//						break;
//	//					}
//	//					Index++;
//	//				}
//	//			}
//
//	//			FString RoleString = HasAuthority() ? TEXT("Host") : TEXT("Client");
//	//			FString WelcomeMessage = FString::Printf(TEXT("You are Player %d (%s)\nNickname: %s"),
//	//				LocalPlayerIndex, *RoleString, *PlayerNickname);
//
//	//			//MainWidgetInstance->SetWelcomeMessage(WelcomeMessage);
//	//		}
//	//	}
//	//}
//}
//
//void ABaseballController::OnRep_PlayerNickName()
//{
//	//if (GetLocalRole() == ROLE_Authority)
//	//{
//	//	FString healthMessage = FString::Printf(TEXT("[Server] %s PlayerNick is"), *GetFName().ToString());
//	//	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, (healthMessage + PlayerNickname));
//	//}
//}
