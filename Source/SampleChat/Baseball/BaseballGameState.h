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

	// ���� ����
	void JoinGame(ABaseballPlayerState* JoinPlayerState, const FString& NewPlayerName);
	// �ٸ� �÷��̾� ����
	void UpdateOtherPlayer();

	UPROPERTY(Replicated)
	TArray<TObjectPtr<ABaseballController>> JoinedPlayerControllers;

private:
	UPROPERTY(Replicated)
	TArray<TObjectPtr<ABaseballPlayerState>> JoinedPlayerStates;

	UPROPERTY(Replicated)
	int32 CurrentTurnPlayerIndex = 0;
};
