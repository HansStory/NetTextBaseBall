// Fill out your copyright notice in the Description page of Project Settings.


#include "Baseball/Widgets/BaseballWidget.h"

#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

#include "Baseball/BaseballController.h"
#include "Baseball/BaseballGameState.h"
#include "GameFramework/PlayerState.h"

void UBaseballWidget::NativeConstruct()
{
	Super::NativeConstruct();

	BindFunction();

	InitWidget();
}

void UBaseballWidget::NativeDestruct()
{
	Super::NativeDestruct();

	LoseFunction();
}

void UBaseballWidget::InitWidget()
{
	SetBaseballPC();

	if (IsValid(BaseballPC->PlayerState))
	{
		FString playerName = BaseballPC->PlayerState->GetPlayerName();

		SetPlayerNameText(playerName);
	}
}

void UBaseballWidget::SetBaseballPC()
{
	if (!IsValid(BaseballPC))
	{
		APlayerController* OwningPlayerController = GetOwningPlayer();
		if (IsValid(OwningPlayerController) == true)
		{
			ABaseballController* OwningBaseballPC = Cast<ABaseballController>(OwningPlayerController);
			if (IsValid(OwningBaseballPC) == true)
			{
				BaseballPC = OwningBaseballPC;
			}
		}
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

void UBaseballWidget::OnClickReadyButton()
{
	if (IsValid(BaseballPC))
	{
		BaseballPC->Server_PlayerReady();
		ReadyButton->SetIsEnabled(false);
	}
}

void UBaseballWidget::SetPlayerNameText(const FString& PlayerName)
{
	if (IsValid(TextMyPlayerName))
	{
		TextMyPlayerName->SetText(FText::FromString(PlayerName));
	}
}


void UBaseballWidget::BindFunction()
{
	if (IsValid(InputChat) && InputChat->OnTextCommitted.IsAlreadyBound(this, &UBaseballWidget::OnInputChatCommitted) == false)
	{
		InputChat->OnTextCommitted.AddDynamic(this, &UBaseballWidget::OnInputChatCommitted);
	}

	if (IsValid(InputPlayerName) && InputPlayerName->OnTextCommitted.IsAlreadyBound(this, &UBaseballWidget::OnInputPlayerNameCommitted) == false)
	{
		InputPlayerName->OnTextCommitted.AddDynamic(this, &UBaseballWidget::OnInputPlayerNameCommitted);
	}

	if (IsValid(InputAnswer) && InputAnswer->OnTextCommitted.IsAlreadyBound(this, &UBaseballWidget::OnInputAnswerCommitted) == false)
	{
		InputAnswer->OnTextCommitted.AddDynamic(this, &UBaseballWidget::OnInputAnswerCommitted);
	}

	if (IsValid(ReadyButton) && ReadyButton->OnClicked.IsAlreadyBound(this, &UBaseballWidget::OnClickReadyButton) == false)
	{
		ReadyButton->OnClicked.AddDynamic(this, &UBaseballWidget::OnClickReadyButton);
	}
}

void UBaseballWidget::LoseFunction()
{
	if (IsValid(InputChat) && InputChat->OnTextCommitted.IsAlreadyBound(this, &UBaseballWidget::OnInputChatCommitted) == true)
	{
		InputChat->OnTextCommitted.RemoveDynamic(this, &UBaseballWidget::OnInputChatCommitted);
	}

	if (IsValid(InputPlayerName) && InputPlayerName->OnTextCommitted.IsAlreadyBound(this, &UBaseballWidget::OnInputPlayerNameCommitted) == true)
	{
		InputPlayerName->OnTextCommitted.RemoveDynamic(this, &UBaseballWidget::OnInputPlayerNameCommitted);
	}

	if (IsValid(InputAnswer) && InputAnswer->OnTextCommitted.IsAlreadyBound(this, &UBaseballWidget::OnInputAnswerCommitted) == true)
	{
		InputAnswer->OnTextCommitted.RemoveDynamic(this, &UBaseballWidget::OnInputAnswerCommitted);
	}

	if (IsValid(ReadyButton) && ReadyButton->OnClicked.IsAlreadyBound(this, &UBaseballWidget::OnClickReadyButton) == true)
	{
		ReadyButton->OnClicked.RemoveDynamic(this, &UBaseballWidget::OnClickReadyButton);
	}
}



