// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class UMyUserWidget;

UCLASS()
class SAMPLECHAT_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UMyUserWidget> WidgetClass;

	UPROPERTY()
	UMyUserWidget* WidgetInstance;

	UFUNCTION(Server, Unreliable, BlueprintCallable, Category = "Message")
	void SendMessageToServer(const FString& Message);
	
	UFUNCTION(Client, Unreliable)
	void ReceiveMessageFromServer(const FString& Message);

	FString GetUserId();
private:
	FString UserId;
};
