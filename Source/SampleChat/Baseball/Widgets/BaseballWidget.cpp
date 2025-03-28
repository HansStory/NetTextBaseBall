// Fill out your copyright notice in the Description page of Project Settings.


#include "Baseball/Widgets/BaseballWidget.h"

#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "Baseball/BaseballController.h"
#include "GameFramework/PlayerState.h"

void UBaseballWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (InputChat->OnTextCommitted.IsAlreadyBound(this, &ThisClass::OnInputChatCommitted) == false)
	{
		InputChat->OnTextCommitted.AddDynamic(this, &ThisClass::OnInputChatCommitted);
	}

	if (InputPlayerName->OnTextCommitted.IsAlreadyBound(this, &ThisClass::OnInputPlayerNameCommitted) == false)
	{
		InputPlayerName->OnTextCommitted.AddDynamic(this, &ThisClass::OnInputPlayerNameCommitted);
	}

	if (InputAnswer->OnTextCommitted.IsAlreadyBound(this, &ThisClass::OnInputAnswerCommitted) == false)
	{
		InputAnswer->OnTextCommitted.AddDynamic(this, &ThisClass::OnInputAnswerCommitted);
	}

	if (!IsValid(BaseballPC))
	{
		APlayerController* OwningPlayerController = GetOwningPlayer();
		if (IsValid(OwningPlayerController) == true)
		{
			ABaseballController* OwningBaseballPC = Cast<ABaseballController>(OwningPlayerController);
			if (IsValid(OwningBaseballPC) == true)
			{
				BaseballPC = OwningBaseballPC;

				if (IsValid(BaseballPC->PlayerState))
				{
					FString playerName = BaseballPC->PlayerState->GetPlayerName();

					SetPlayerNameText(playerName);
				}

			}
		}
	}
}

void UBaseballWidget::NativeDestruct()
{
	Super::NativeDestruct();

	if (InputChat->OnTextCommitted.IsAlreadyBound(this, &ThisClass::OnInputChatCommitted) == true)
	{
		InputChat->OnTextCommitted.RemoveDynamic(this, &ThisClass::OnInputChatCommitted);
	}

	if (InputPlayerName->OnTextCommitted.IsAlreadyBound(this, &ThisClass::OnInputPlayerNameCommitted) == true)
	{
		InputPlayerName->OnTextCommitted.RemoveDynamic(this, &ThisClass::OnInputPlayerNameCommitted);
	}

	if (InputAnswer->OnTextCommitted.IsAlreadyBound(this, &ThisClass::OnInputAnswerCommitted) == true)
	{
		InputAnswer->OnTextCommitted.RemoveDynamic(this, &ThisClass::OnInputAnswerCommitted);
	}
}

void UBaseballWidget::OnInputChatCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::OnEnter)
	{
		if (IsValid(BaseballPC))
		{
			BaseballPC->Server_SendMessage(Text.ToString());
			InputChat->SetText(FText());
		}
	}
}

void UBaseballWidget::OnInputPlayerNameCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::OnEnter)
	{
		if (IsValid(BaseballPC))
		{
			BaseballPC->Server_SetPlayerName(Text.ToString());
			InputPlayerName->SetText(FText());
		}
	}
}

void UBaseballWidget::OnInputAnswerCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::OnEnter)
	{
		if (IsValid(BaseballPC))
		{
			BaseballPC->Server_SendAnswer(Text.ToString());
			InputAnswer->SetText(FText());
		}
	}
}

void UBaseballWidget::SetPlayerNameText(const FString& PlayerName)
{
	if (IsValid(TextMyPlayerName))
	{
		TextMyPlayerName->SetText(FText::FromString(PlayerName));
	}
}

void UBaseballWidget::UpdateOtherPlayerName(const FString& Name)
{
	if (IsValid(TextOtherPlayerName))
	{
		TextOtherPlayerName->SetText(FText::FromString(Name));
	}
}

