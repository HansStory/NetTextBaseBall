// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BaseballFunctionLibrary.generated.h"


UCLASS()
class SAMPLECHAT_API UBaseballFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "BaseballFunctionLibrary")
	static FString GenerateRandomNum();

	UFUNCTION(BlueprintCallable, Category = "BaseballFunctionLibrary")
	static FString ValidateAndCheckInput(const FString& Input, const FString& GenerateNum);
	
};
