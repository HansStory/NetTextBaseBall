// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

class UScrollBox;
class UVerticalBox;
class UTextBlock;

class UChatMessageWidget;
class UPlayerListItemWidget;

UCLASS()
class SAMPLECHAT_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
    virtual void NativeConstruct() override;

public:
    // 플레이어 참가
    void SetPlayerName(int32 Index, const FString& PlayerName);


    TArray<TObjectPtr<UPlayerListItemWidget>> PlayerTexts;




    // =================================

    void AddChatMessage(const FString& Message);
    void AddPlayerToList(const FString& PlayerName, int32 PlayerIndex);
    void ClearPlayerList();

    UPROPERTY(meta = (BindWidget))
    UScrollBox* ChatScrollBox;

    UPROPERTY(meta = (BindWidget))
    UVerticalBox* PlayerListBox;

    UPROPERTY(EditAnywhere, Category = "UI")
    TSubclassOf<UChatMessageWidget> ChatMessageClass;

    UPROPERTY(EditAnywhere, Category = "UI")
    TSubclassOf<UPlayerListItemWidget> PlayerListItemClass;
	
};
