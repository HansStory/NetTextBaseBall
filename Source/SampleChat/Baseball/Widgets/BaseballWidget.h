// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseballWidget.generated.h"

class UTextBlock;
class UEditableTextBox;
class UButton;

class ABaseballController;

UCLASS()
class SAMPLECHAT_API UBaseballWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

protected:
	UFUNCTION()
	void OnInputChatCommitted(const FText& Text, ETextCommit::Type CommitMethod);

	UFUNCTION()
	void OnInputPlayerNameCommitted(const FText& Text, ETextCommit::Type CommitMethod);

	UFUNCTION()
	void OnInputAnswerCommitted(const FText& Text, ETextCommit::Type CommitMethod);

	UFUNCTION()
	void OnClickReadyButton();

public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UEditableTextBox> InputChat;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UEditableTextBox> InputPlayerName;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UEditableTextBox> InputAnswer;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ReadyButton;
	
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextMyPlayerName;

	void SetPlayerNameText(const FString& PlayerName);
	void SetInputAnswerEnable(bool bIsEnable);
	void OnGameStart();
	void OnGameReset();

private:
	void BindFunction();
	void LoseFunction();

	void InitWidget();
	void SetBaseballPC();
	TObjectPtr<ABaseballController> BaseballPC = nullptr;
};
