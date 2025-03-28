// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "BaseballGameState.generated.h"

class ABaseballPlayerState;
class ABaseballController;


UCLASS()
class SAMPLECHAT_API ABaseballGameState : public AGameStateBase
{
	GENERATED_BODY()
	
	
public:
	ABaseballGameState();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// 게임 참가
	void JoinGame(ABaseballPlayerState* JoinPlayerState, const FString& NewPlayerName);
	// 다른 플레이어 참가
	void UpdateOtherPlayer();

	UPROPERTY(Replicated)
	TArray<TObjectPtr<ABaseballController>> JoinedPlayerControllers;

private:
	UPROPERTY(Replicated)
	TArray<TObjectPtr<ABaseballPlayerState>> JoinedPlayerStates;

	UPROPERTY(Replicated)
	int32 CurrentTurnPlayerIndex = 0;
};
