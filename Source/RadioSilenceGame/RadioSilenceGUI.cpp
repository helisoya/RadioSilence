// Fill out your copyright notice in the Description page of Project Settings.


#include "RadioSilenceGUI.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "RadioSilenceGameInstance.h"
#include "Components/CanvasPanel.h"
#include "DayNightCycle.h"
#include "Logging/StructuredLog.h"
#include "Components/CanvasPanelSlot.h"
#include "MapIconWidget.h"

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

	RefreshTimeText();

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

	gameInstance = Cast<URadioSilenceGameInstance>(GetGameInstance());
	if (gameInstance) {
		gameInstance->gui = this;
	}
}

bool URadioSilenceGUI::IsPaused()
{
	return paused;
}

void URadioSilenceGUI::RefreshTimeText()
{
	if (!gameInstance) return;

	FString str = FString::FromInt(gameInstance->dayNightCycle->GetHour());
	str.Append(":");
	str.Append(FString::FromInt(gameInstance->dayNightCycle->GetMinutes()));

	UE_LOGFMT(LogCore, Warning, "Hour : {1}, Seconds : {2}", gameInstance->dayNightCycle->GetHour(), gameInstance->dayNightCycle->GetMinutes());

	TimeText->SetText(FText::FromString(str));
}

void URadioSilenceGUI::AddIconToMap(UMapIconWidget* widget)
{
	widget->SetSlot(MapRoot->AddChildToCanvas(widget));
}

void URadioSilenceGUI::RemoveIconFromMap(UUserWidget* widget)
{
	MapRoot->RemoveChild(widget);
}


