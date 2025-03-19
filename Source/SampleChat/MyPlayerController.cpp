#include "MyPlayerController.h"
#include "MyGameModeBase.h"
#include "MyUserWidget.h"
#include "Kismet/KismetSystemLibrary.h"

void AMyPlayerController::BeginPlay()
{
	bShowMouseCursor = true;

	SetInputMode(FInputModeUIOnly());

	//UE_LOG(LogTemp, Log, TEXT("Player Controller Start!!"));

	if (HasAuthority())
	{
		UE_LOG(LogTemp, Log, TEXT("Im Host:%d Authority Player Controller!!"), this->GetUniqueID());
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Im Guest : %d Authority Player Controller!!"), this->GetUniqueID());
	}

	bool bIsServer = UKismetSystemLibrary::IsServer(GetWorld());

	// UserId 설정
	if (bIsServer)
	{
		UserId = "Host";  // 서버인 경우 "Host"
	}
	else
	{
		UserId = "Guest"; // 클라이언트인 경우 "Guest"
	}

	if (IsLocalController())
	{
		if (WidgetClass && WidgetInstance == nullptr)
		{
			WidgetInstance = CreateWidget<UMyUserWidget>(this, WidgetClass);
		}

		WidgetInstance->AddToViewport();
		WidgetInstance->SetOwningPlayer(this);
	}

	FString FormattedMessage = FString::Printf(TEXT("[%s]: Hellow"), *UserId);
	SendMessageToServer(FormattedMessage);
}

FString AMyPlayerController::GetUserId()
{
	return UserId;
}


// Message
void AMyPlayerController::SendMessageToServer_Implementation(const FString& Message)
{
	UE_LOG(LogTemp, Log, TEXT("[Server] RPC from client : %s"), *Message);

	AMyGameModeBase* GameMode = Cast<AMyGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->GotMessageFromClient(this, Message);
	}
}

void AMyPlayerController::ReceiveMessageFromServer_Implementation(const FString& Message)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, Message);
}