// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BaseballHUD.generated.h"

/**
 * 
 */
UCLASS()
class SAMPLECHAT_API ABaseballHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class UEntryWidget> EntryWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class UMainWidget> MainWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class UResultWidget> ResultWidgetClass;

	UPROPERTY()
	UEntryWidget* EntryWidgetInstance;
	UPROPERTY()
	UMainWidget* MainWidgetInstance;
	UPROPERTY()
	UResultWidget* ResultWidgetInstance;
	
	
};
