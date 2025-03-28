// Fill out your copyright notice in the Description page of Project Settings.


#include "Baseball/BaseballFunctionLibrary.h"

FString UBaseballFunctionLibrary::GenerateRandomNum()
{
	constexpr int32 NumLength = 3;
	FString RandomNumber;
	const FRandomStream RandStream(FDateTime::Now().GetTicks());

	while (RandomNumber.Len() < NumLength)
	{
		int32 RandNumber = RandStream.RandRange(1, 9);

		if (!RandomNumber.Contains(FString::FromInt(RandNumber)))
		{
			RandomNumber += FString::FromInt(RandNumber);
		}
	}

	return RandomNumber;
}

FString UBaseballFunctionLibrary::ValidateAndCheckInput(const FString& Input, const FString& GenerateNum)
{
	// �Է� ����
	if (!Input.StartsWith("/"))
	{
		return FString(TEXT("[Error] / �Է����� ���� : OUT"));
	}

	FString Guess = Input.Mid(1); // '/' ������ ���ڿ� ����

	if (Guess.Len() != 3)
	{
		return FString(TEXT("[Error] �Է� ���� �ʰ� : OUT"));
	}
	else if (!Guess.IsNumeric())
	{
		return FString(TEXT("[Error] ���ڰ� �ƴ� : OUT"));
	}

	// �ߺ� ���� �˻�
	TSet<TCHAR> UniqueDigits;
	for (TCHAR Digit : Guess)
	{
		if (Digit < '1' || Digit > '9' || UniqueDigits.Contains(Digit))
		{
			return FString(TEXT("[Error] �ߺ��� �� �Է� : OUT"));
		}
		UniqueDigits.Add(Digit);
	}

	// ��Ʈ����ũ �� �� ���� ���
	int32 Strikes = 0;
	int32 Balls = 0;

	for (int32 i = 0; i < 3; i++)
	{
		if (Guess[i] == GenerateNum[i])
		{
			Strikes++;
		}
		else if (GenerateNum.Contains(FString(1, &Guess[i])))
		{
			Balls++;
		}
	}

	// ��� ��ȯ
	if (Strikes == 3)
	{
		return FString(TEXT("3S 0B �� Win"));
	}
	else if (Strikes == 0 && Balls == 0)
	{
		return "OUT";
	}
	else
	{
		return FString::Printf(TEXT("%dS %dB"), Strikes, Balls);
	}
}
