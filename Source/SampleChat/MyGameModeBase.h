#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"


UCLASS()
class SAMPLECHAT_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AMyGameModeBase();

	UFUNCTION(Server, Reliable, WithValidation)
	void GotMessageFromClient(APlayerController* PlayerController, const FString& Message);
	
	
	
};
