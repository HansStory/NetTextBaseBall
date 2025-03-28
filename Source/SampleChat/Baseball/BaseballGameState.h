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

protected:
	virtual void BeginPlay() override;
	
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
};
