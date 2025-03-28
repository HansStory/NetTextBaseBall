#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "BaseballGameMode.generated.h"

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

	void GenerateRandomNum();

	UFUNCTION(Server, Reliable, WithValidation)
	void RecieveMessageFromClient(APlayerController* PlayerController, const FString& Message);
	void SendMessageToClient(APlayerController* PlayerController, const FString& Message);

	UFUNCTION(NetMulticast, Unreliable)
	void Multicast_BroadcastMessage(const FString& Message);

	void SetPlayerNickname(APlayerController* PlayerController, const FString& NewName);



	FORCEINLINE void SetRequiredReadyCount(const int32 InRequiredReadyCount) { RequiredReadyCount = InRequiredReadyCount; }
	
private:
	// 필요 플레이어 수
	int32 RequiredReadyCount;

	TArray<TObjectPtr<ABaseballController>> AllPlayerControllers;

	FString ServerGenerateNum;
};
