// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "BaseballPlayerState.generated.h"

class ABaseballController;

UCLASS()
class SAMPLECHAT_API ABaseballPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
    ABaseballPlayerState();

    ABaseballController* GetBaseballController() const;

	void OnRep_PlayerName() override;

protected:

};
