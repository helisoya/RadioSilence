// Fill out your copyright notice in the Description page of Project Settings.


#include "RadioSilenceGUI.h"
#include "Components/TextBlock.h"

void URadioSilenceGUI::SetInteractionText(FString newText)
{
	InteractionText->SetText(FText::FromString(newText));
}
