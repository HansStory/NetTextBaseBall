// Fill out your copyright notice in the Description page of Project Settings.


#include "Baseball/Widgets/MainWidget.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "Components/VerticalBox.h"
#include "Baseball/Widgets/ChatMessageWidget.h"
#include "Baseball/Widgets/PlayerListItemWidget.h"

#include "Baseball/BaseballController.h"
#include "Baseball/BaseballGameState.h"


void UMainWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (ABaseballController* BaseballPC = Cast<ABaseballController>(GetOwningPlayer()))
    {
        if (AGameStateBase* GameState = BaseballPC->GetWorld()->GetGameState())
        {
            if (ABaseballGameState* BaseballGS = Cast<ABaseballGameState>(GameState))
            {
                for (int i = 0; i < BaseballGS->JoinedPlayerControllers.Num(); i++)
                {
                    UPlayerListItemWidget* TextBlock = CreateWidget<UPlayerListItemWidget>(this, PlayerListItemClass);
                    PlayerTexts.Add(TextBlock);

                    if (PlayerListBox)
                    {
                        PlayerListBox->AddChildToVerticalBox(TextBlock);
                    }
                }
            }
        }
    }

}

void UMainWidget::SetPlayerName(int32 Index, const FString& PlayerName)
{
    if (PlayerTexts.IsValidIndex(Index))
    {
        PlayerTexts[Index]->PlayerInfoText->SetText(FText::FromString(PlayerName));
    }
}

void UMainWidget::AddChatMessage(const FString& Message)
{
    //auto text = FText::FromString(Message);
    //UE_LOG(LogTemp, Log, TEXT(Message);
    if (ChatScrollBox && ChatMessageClass)
    {
        UChatMessageWidget* NewMessage = CreateWidget<UChatMessageWidget>(this, ChatMessageClass);

        if (NewMessage)
        {
            NewMessage->SetMessage(Message);
            ChatScrollBox->AddChild(NewMessage);
            ChatScrollBox->ScrollToEnd();
        }
    }
}

void UMainWidget::AddPlayerToList(const FString& PlayerName, int32 PlayerIndex)
{
    //UE_LOG(LogTemp, Log, TEXT("%s", PlayerName));

    if (PlayerListBox && PlayerListItemClass)
    {
        UPlayerListItemWidget* PlayerItem = CreateWidget<UPlayerListItemWidget>(this, PlayerListItemClass);
        if (PlayerItem)
        {
            PlayerItem->SetPlayerInfo(PlayerName, PlayerIndex);
            PlayerListBox->AddChild(PlayerItem);
        }
    }
}

void UMainWidget::ClearPlayerList()
{
    if (PlayerListBox)
    {
        PlayerListBox->ClearChildren();
    }
}
