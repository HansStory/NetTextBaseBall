#include "Baseball/BaseballPlayerState.h"

#include "Baseball/BaseballController.h"
#include "Net/UnrealNetwork.h"


ABaseballPlayerState::ABaseballPlayerState()
{
	bReplicates = true;
}

ABaseballController* ABaseballPlayerState::GetBaseballController() const
{
	ABaseballController* BaseballPC = nullptr;

	if (GetPlayerController())
	{
		BaseballPC = Cast<ABaseballController>(GetPlayerController());
	}

	return BaseballPC;
}

void ABaseballPlayerState::OnRep_PlayerName()
{
	Super::OnRep_PlayerName();

	FString ChangedName = GetPlayerName();

	UE_LOG(LogTemp, Log, TEXT("OnRep_PlayerName() => Player Name Changed : %s "), *ChangedName);

	if (ABaseballController* BaseballPC = Cast<ABaseballController>(GetPlayerController()))
	{
		BaseballPC->SetPlayerName(*ChangedName);
	}
}
