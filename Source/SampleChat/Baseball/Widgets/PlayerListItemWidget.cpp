// Fill out your copyright notice in the Description page of Project Settings.


#include "Baseball/Widgets/PlayerListItemWidget.h"
#include "Components/TextBlock.h"

void UPlayerListItemWidget::SetPlayerInfo(const FString& PlayerName, int32 PlayerIndex)
{
    if (PlayerInfoText)
    {
        FString DisplayText = FString::Printf(TEXT("%d. %s"), PlayerIndex, *PlayerName);
        PlayerInfoText->SetText(FText::FromString(DisplayText));
    }
}
