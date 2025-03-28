// Fill out your copyright notice in the Description page of Project Settings.


#include "Baseball/Widgets/ChatMessageWidget.h"
#include "Components/TextBlock.h"

void UChatMessageWidget::SetMessage(const FString& Message)
{
    if (MessageText)
    {
        MessageText->SetText(FText::FromString(Message));
    }
}
