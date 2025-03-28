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

	if (ABaseballController* BaseballPC = Cast<ABaseballController>(GetPlayerController()))
	{
		BaseballPC->SetPlayerName(GetPlayerName());
	}
}
