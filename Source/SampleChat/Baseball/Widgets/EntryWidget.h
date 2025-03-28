#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EntryWidget.generated.h"

UCLASS()
class SAMPLECHAT_API UEntryWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
public:
	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* InputUserId;
	UPROPERTY(meta = (BindWidget))
	class UButton* ButtonSetUserId;

protected:
	UFUNCTION()
	void OnClickSetUserIdButton();

};
