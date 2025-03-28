#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BaseballController.generated.h"

class UBaseballWidget;
class UEntryWidget;
class UMainWidget;
class UResultWidget;

UCLASS()
class SAMPLECHAT_API ABaseballController : public APlayerController
{
	GENERATED_BODY()

protected:
	void BeginPlay() override;

public:
	void OnRep_PlayerState() override;

#pragma region Widgets Classes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UBaseballWidget> BaseballWidgetClass;
	UPROPERTY()
	TObjectPtr<UBaseballWidget> BaseballWidgetInstance;

	//// Entry Widget
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	//TSubclassOf<UEntryWidget> EntryWidgetClass;
	//UPROPERTY()
	//TObjectPtr<UEntryWidget> EntryWidgetInstance;

	//// Main Widget
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	//TSubclassOf<UMainWidget> MainWidgetClass;
	//UPROPERTY()
	//TObjectPtr<UMainWidget> MainWidgetInstance;

	//// Result Widget
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	//TSubclassOf<UResultWidget> ResultWidgetClass;
	//UPROPERTY()
	//TObjectPtr<UResultWidget> ResultWidgetInstance;
#pragma endregion

	UFUNCTION(Server, Reliable)
	void Server_SendMessage(const FString& Message);

	UFUNCTION(Server, Reliable)
	void Server_SetPlayerName(const FString& Message);

	UFUNCTION(Server, Reliable)
	void Server_SendAnswer(const FString& Answer);


	UFUNCTION(Server, Reliable)
	void Server_PlayerReady();


	UFUNCTION(Client, Reliable)
	void Client_ReceiveMessage(const FString& Message);

	UFUNCTION(Client, Reliable)
	void Client_ReceiveAnswer(const FString& Message);

	UFUNCTION(Client, Reliable)
	void Client_OnGameStart();

	UFUNCTION(Client, Reliable)
	void Client_OnGameEnd();

	UFUNCTION(Client, Reliable)
	void Client_OnGameReset();

	void SetPlayerName(const FString& PlayerName);

};
