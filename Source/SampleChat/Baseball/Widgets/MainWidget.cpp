// Fill out your copyright notice in the Description page of Project Settings.


#include "Baseball/Widgets/MainWidget.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "Components/VerticalBox.h"
#include "Baseball/Widgets/ChatMessageWidget.h"
#include "Baseball/Widgets/PlayerListItemWidget.h"

#include "Baseball/BaseballController.h"
#include "Baseball/BaseballGameState.h"
#include "Baseball/BaseballPlayerState.h"


void UMainWidget::NativeConstruct()
{
    Super::NativeConstruct();





    //if (ABaseballController* BaseballPC = Cast<ABaseballController>(GetOwningPlayer()))
    //{
    //    if (AGameStateBase* GameState = BaseballPC->GetWorld()->GetGameState())
    //    {
    //        if (ABaseballGameState* BaseballGS = Cast<ABaseballGameState>(GameState))
    //        {
    //            for (int i = 0; i < BaseballGS->JoinedPlayerControllers.Num(); i++)
    //            {
    //                UPlayerListItemWidget* TextBlock = CreateWidget<UPlayerListItemWidget>(this, PlayerListItemClass);
    //                PlayerTexts.Add(TextBlock);

    //                if (PlayerListBox)
    //                {
    //                    PlayerListBox->AddChildToVerticalBox(TextBlock);
    //                }
    //            }
    //        }
    //    }
    //}

}

void UMainWidget::InitMainWidget(const TArray<ABaseballPlayerState*>& PlayerStates)
{
    for (ABaseballPlayerState* BaseballPS : PlayerStates)
    {
        //ABaseballPlayerState* BaseballPS = Cast<ABaseballPlayerState>(PS);
        if (BaseballPS)
        {
            //PlayerStates.Add(BaseballPS);

            int32 PlayerId = BaseballPS->GetUniqueID();
            FString PlayerName = BaseballPS->GetPlayerName();

            //
            UTextBlock* NewTextBlock = NewObject<UTextBlock>(this);
            if (NewTextBlock)
            {
                NewTextBlock->SetText(FText::FromString(PlayerName));
                PlayerListBox->AddChild(NewTextBlock);
                PlayerNameWidgets.Add(PlayerId, NewTextBlock);
            }
        }
    }

    //AGameStateBase* GameState = GetWorld()->GetGameState();
    //if (GameState)
    //{
    //    // TArray<TObjectPtr<ABaseballPlayerState>> PlayerStates;
    //    for (APlayerState* PS : PlayerStates)
    //    {
    //        ABaseballPlayerState* BaseballPS = Cast<ABaseballPlayerState>(PS);
    //        if (BaseballPS)
    //        {
    //            //PlayerStates.Add(BaseballPS);

    //            int32 PlayerId = BaseballPS->GetUniqueID();
    //            FString PlayerName = BaseballPS->GetPlayerName();

    //            //
    //            UTextBlock* NewTextBlock = NewObject<UTextBlock>(this);
    //            if (NewTextBlock)
    //            {
    //                NewTextBlock->SetText(FText::FromString(PlayerName));
    //                PlayerListBox->AddChild(NewTextBlock);
    //                PlayerNameWidgets.Add(PlayerId, NewTextBlock);
    //            }
    //        }
    //    }
    //}

    //APlayerController* OwningPlayerController = GetOwningPlayer();
    //if (IsValid(OwningPlayerController) == true)
    //{
    //    TArray<TObjectPtr<ABaseballPlayerState>> PlayerStates;
    //    //for(APlayerState* PS : )
    //}
}

void UMainWidget::SetPlayerNameText(const FString& PlayerName)
{
    //if (PlayerNameWidgets.Num() > 0)
    //{
    //    auto baseballPlayerState = GetOwningPlayer<ABaseballController>();
    //    if (baseballPlayerState)
    //    {
    //        UE_LOG(LogTemp, Error, TEXT("Unique ID is : %d"), baseballPlayerState->GetUniqueID());
    //        if (IsValid(PlayerNameWidgets[baseballPlayerState->GetUniqueID()]))
    //        {
    //            PlayerNameWidgets[0]->SetText(FText::FromString(PlayerName));
    //        }
    //    }
    //}
}

















//void UMainWidget::SetPlayerName(int32 Index, const FString& PlayerName)
//{
//    if (PlayerTexts.IsValidIndex(Index))
//    {
//        PlayerTexts[Index]->PlayerInfoText->SetText(FText::FromString(PlayerName));
//    }
//}
//
//void UMainWidget::AddChatMessage(const FString& Message)
//{
//    //auto text = FText::FromString(Message);
//    //UE_LOG(LogTemp, Log, TEXT(Message);
//    if (ChatScrollBox && ChatMessageClass)
//    {
//        UChatMessageWidget* NewMessage = CreateWidget<UChatMessageWidget>(this, ChatMessageClass);
//
//        if (NewMessage)
//        {
//            NewMessage->SetMessage(Message);
//            ChatScrollBox->AddChild(NewMessage);
//            ChatScrollBox->ScrollToEnd();
//        }
//    }
//}
//
//void UMainWidget::AddPlayerToList(const FString& PlayerName, int32 PlayerIndex)
//{
//    //UE_LOG(LogTemp, Log, TEXT("%s", PlayerName));
//
//    if (PlayerListBox && PlayerListItemClass)
//    {
//        UPlayerListItemWidget* PlayerItem = CreateWidget<UPlayerListItemWidget>(this, PlayerListItemClass);
//        if (PlayerItem)
//        {
//            PlayerItem->SetPlayerInfo(PlayerName, PlayerIndex);
//            PlayerListBox->AddChild(PlayerItem);
//        }
//    }
//}
//
//void UMainWidget::ClearPlayerList()
//{
//    if (PlayerListBox)
//    {
//        PlayerListBox->ClearChildren();
//    }
//}
