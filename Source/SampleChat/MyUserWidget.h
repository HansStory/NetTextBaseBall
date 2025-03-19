// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"


UCLASS()
class SAMPLECHAT_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
public:
	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* EditableText;
	
	UFUNCTION(BlueprintCallable)
	void OnTextCommittedFunction(const FText& Text, const ETextCommit::Type CommitMethod);
	
};
