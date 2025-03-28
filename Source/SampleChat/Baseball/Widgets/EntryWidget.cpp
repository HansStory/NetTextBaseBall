#include "Baseball/Widgets/EntryWidget.h"

#include "Components/Button.h"
#include "Components/EditableTextBox.h"

#include "Baseball/BaseballController.h"
#include "GameFramework/PlayerState.h"

void UEntryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ButtonSetUserId)
	{
		ButtonSetUserId->OnClicked.AddDynamic(this, &UEntryWidget::OnClickSetUserIdButton);
	}
}

void UEntryWidget::OnClickSetUserIdButton()
{
	if (InputUserId)
	{
		FString IDText = InputUserId->GetText().ToString();
		if (!IDText.IsEmpty())
		{
			if (ABaseballController* BaseballPC = Cast<ABaseballController>(GetOwningPlayer()))
			{
				if (IsValid(BaseballPC))
				{
					BaseballPC->Server_SetPlayerName(IDText);
					InputUserId->SetText(FText());
				}

				//FString PlayerName = BaseballPC->PlayerState->GetPlayerName();
				//UE_LOG(LogTemp, Warning, TEXT("%s"), *PlayerName);

				//BaseballPC->PlayerState->SetPlayerName(IDText);
				//BaseballPC->Server_JoinGame(IDText);

				//RemoveFromParent();
			}
		}

	}
}
