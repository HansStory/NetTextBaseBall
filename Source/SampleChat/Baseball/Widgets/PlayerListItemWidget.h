// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerListItemWidget.generated.h"


UCLASS()
class SAMPLECHAT_API UPlayerListItemWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* PlayerInfoText;

	void SetPlayerInfo(const FString& PlayerName, int32 PlayerIndex);
	
	
};
