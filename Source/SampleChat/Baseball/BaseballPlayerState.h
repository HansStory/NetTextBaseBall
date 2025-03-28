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
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    ABaseballController* GetBaseballController() const;

	void OnRep_PlayerName() override;

	//void SetReady(bool isReady);

	int32 GetTryCount() { return TryCount; }
	void IncreseTryCount();

protected:
	UPROPERTY(Replicated)
	int32 TryCount = 0;
	int32 MaxTryCount = 3;

	//bool bIsReady = false;

};
