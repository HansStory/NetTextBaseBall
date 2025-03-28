#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "BaseballGameMode.generated.h"

UENUM(BlueprintType)
enum class EGameState : uint8
{
	Waiting = 0,
	Playing,
	GameOver
};

class ABaseballController;

UCLASS()
class SAMPLECHAT_API ABaseballGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABaseballGameMode();
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void PostLogin(APlayerController* NewPlayer) override;

	UFUNCTION(Server, Reliable, WithValidation)
	void RecieveMessageFromClient(APlayerController* PlayerController, const FString& Message);
	void SendMessageToClient(APlayerController* PlayerController, const FString& Message);
	void SendMessageToAllClient(const FString& Message);

	UFUNCTION(NetMulticast, Unreliable)
	void Multicast_BroadcastMessage(const FString& Message);

	void SetPlayerNickname(APlayerController* PlayerController, const FString& NewName);

	//UFUNCTION(Server, Reliable)
	void ReceiveAnswerFromClient(APlayerController* PlayerController, const FString& Answer);


	void PlayerReady(APlayerController* PlayerController);

	void GenerateRandomNum();
	FString GetGeneratedNum() { return ServerGenerateNum; }
	FString ValidateAndCheckGuess(const FString& Input, const FString& SecretNumber);

private:
	TArray<TObjectPtr<ABaseballController>> AllPlayerControllers;
	int32 ReadyCount = 0;

	FString ServerGenerateNum;

	EGameState CurrentGameState = EGameState::Waiting;
	void GameStart();
	void GameEnd();
};
