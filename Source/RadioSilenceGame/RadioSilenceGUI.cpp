// Fill out your copyright notice in the Description page of Project Settings.


#include "RadioSilenceGUI.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"

void URadioSilenceGUI::SetInteractionText(FString newText)
{
	InteractionText->SetText(FText::FromString(newText));
}

void URadioSilenceGUI::OpenPauseMenu()
{
	if (playerController == nullptr) return;

	playerController->SetInputMode(FInputModeGameAndUI());
	playerController->bShowMouseCursor = true;

	NormalCanvas->SetVisibility(ESlateVisibility::Hidden);
	PauseCanvas->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

	playerController->SetPause(true);
}

void URadioSilenceGUI::ClosePauseMenu()
{
	if (playerController == nullptr) return;

	playerController->SetInputMode(FInputModeGameOnly());
	playerController->bShowMouseCursor = false;


	NormalCanvas->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	PauseCanvas->SetVisibility(ESlateVisibility::Hidden);

	playerController->SetPause(false);
}

void URadioSilenceGUI::QuitGame()
{
	UE_LOG(LogTemp, Display, TEXT("Exiting the game..."));
	FGenericPlatformMisc::RequestExit(false);
}

void URadioSilenceGUI::Init(APlayerController* controller)
{
	this->playerController = controller;

	PauseQuitButton->OnClicked.AddUniqueDynamic(this, &URadioSilenceGUI::QuitGame);
	PauseResumeButton->OnClicked.AddUniqueDynamic(this, &URadioSilenceGUI::ClosePauseMenu);

	ClosePauseMenu();
}

bool URadioSilenceGUI::IsPaused()
{
	return paused;
}
