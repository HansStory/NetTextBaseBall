#include "MyUserWidget.h"
#include "Components/EditableTextBox.h"
#include "Components/EditableText.h"
#include "MyPlayerController.h"

void UMyUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (IsValid(EditableText))
	{
		EditableText->OnTextCommitted.AddDynamic(this, &UMyUserWidget::OnTextCommittedFunction);

		AMyPlayerController* Controller = Cast<AMyPlayerController>(GetOwningPlayer());
		if (!Controller)
		{
			UE_LOG(LogTemp, Error, TEXT("PlayerController is NULL!"));
			return;
		}

		EditableText->SetText(FText::FromString(Controller->GetUserId()));
	}
}

void UMyUserWidget::OnTextCommittedFunction(const FText& Text, const ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::OnEnter)
	{
		if (Text.IsEmpty()) return;

		AMyPlayerController* Controller = Cast<AMyPlayerController>(GetOwningPlayer());
		if (!Controller)
		{
			UE_LOG(LogTemp, Error, TEXT("PlayerController is NULL!"));
			return;
		}

		FString FormattedMessage = FString::Printf(TEXT("[%s]: %s"), *Controller->GetUserId(), *Text.ToString());
		Controller->SendMessageToServer(FormattedMessage);
		EditableText->SetText(FText::FromString(""));
	}
}
