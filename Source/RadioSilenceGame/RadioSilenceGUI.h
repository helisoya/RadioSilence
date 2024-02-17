// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RadioSilenceGUI.generated.h"


/**
 * 
 */
UCLASS()
class RADIOSILENCEGAME_API URadioSilenceGUI : public UUserWidget
{
	GENERATED_BODY()

public :

	/** Changes the interaction text **/
	void SetInteractionText(FString newText);

	UPROPERTY(EditAnywhere,meta=(BindWidget))
	class UTextBlock* InteractionText;
	
};
