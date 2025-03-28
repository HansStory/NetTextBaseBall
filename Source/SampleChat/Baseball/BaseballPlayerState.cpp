#include "Baseball/BaseballPlayerState.h"

#include "Baseball/BaseballController.h"
#include "Net/UnrealNetwork.h"


ABaseballPlayerState::ABaseballPlayerState()
{
	bReplicates = true;
}

void ABaseballPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABaseballPlayerState, TryCount);
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

void ABaseballPlayerState::IncreseTryCount()
{
	TryCount++;
}

//void ABaseballPlayerState::SetReady(bool isReady)
//{
//	bIsReady = isReady;
//}
