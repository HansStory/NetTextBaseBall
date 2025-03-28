#include "Baseball/BaseballGameState.h"

#include "Baseball/BaseballGameMode.h"
#include "Baseball/BaseballPlayerState.h"
#include "Baseball/BaseballController.h"

#include "Net/UnrealNetwork.h"

ABaseballGameState::ABaseballGameState()
{
	bReplicates = true;
}

void ABaseballGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABaseballGameState, JoinedPlayerStates);
	DOREPLIFETIME(ABaseballGameState, JoinedPlayerControllers);
}

void ABaseballGameState::JoinGame(ABaseballPlayerState* JoinPlayerState, const FString& NewPlayerName)
{
	JoinPlayerState->SetPlayerName(NewPlayerName);

	UE_LOG(LogTemp, Warning, TEXT("NewPlayer Name : %s"), *NewPlayerName);

	JoinedPlayerStates.Add(JoinPlayerState);
	ABaseballController* BaseballPC = JoinPlayerState->GetBaseballController();
	if (BaseballPC)
	{
		JoinedPlayerControllers.Add(BaseballPC);
		BaseballPC->Client_JoinGame(JoinedPlayerStates.Num() == 1);
	}

	if (ABaseballGameMode* BaseballGM = Cast<ABaseballGameMode>(GetWorld()->GetAuthGameMode()))
	{
		//BaseballGM->SetRequiredReadyCount(JoinedPlayerStates.Num());
	}

	UpdateOtherPlayer();
}

void ABaseballGameState::UpdateOtherPlayer()
{
	for (const ABaseballController* BaseballPC : JoinedPlayerControllers)
	{
		if (BaseballPC)
		{
			int32 Index = 1;
			for (const ABaseballPlayerState* BaseballPS : JoinedPlayerStates)
			{
				if (BaseballPS)
				{
					int32 TargetIndex = 0;
					if (BaseballPS != BaseballPC->PlayerState)
					{
						TargetIndex = Index++;
					}

					BaseballPC->Client_UpdateOtherPlayerName(TargetIndex, BaseballPS->GetPlayerName());
				}
			}
		}
	}
}
