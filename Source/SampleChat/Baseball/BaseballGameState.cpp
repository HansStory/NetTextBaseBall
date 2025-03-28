#include "Baseball/BaseballGameState.h"

#include "Baseball/BaseballGameMode.h"
#include "Baseball/BaseballPlayerState.h"
#include "Baseball/BaseballController.h"

#include "Net/UnrealNetwork.h"

ABaseballGameState::ABaseballGameState()
{
	bReplicates = true;
}

void ABaseballGameState::BeginPlay()
{

}

void ABaseballGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

}
