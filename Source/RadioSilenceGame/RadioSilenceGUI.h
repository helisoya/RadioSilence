// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RadioSilenceGUI.generated.h"

class UMapIconWidget;

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

	/** Opens the pause menu **/
	void OpenPauseMenu();

	UFUNCTION()
	/** Closes the pause menu **/
	void ClosePauseMenu();

	UFUNCTION()
	/** Quit the game **/
	void QuitGame();

	/** Initialize the  **/
	void Init(APlayerController* controller);

	/** Returns if the game is paused or not **/
	bool IsPaused();
	
	/** Refreshs the time on the GUI **/
	void RefreshTimeText();

	/** Add a widget to the map **/
	void AddIconToMap(UMapIconWidget* widget);

	/** Remove a widget from the map **/
	void RemoveIconFromMap(UUserWidget* widget);

	UPROPERTY(EditAnywhere,meta=(BindWidget))
	class UTextBlock* InteractionText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UCanvasPanel* NormalCanvas;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UCanvasPanel* PauseCanvas;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* PauseResumeButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* PauseQuitButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* TimeText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UCanvasPanel* MapRoot;

private :

	UPROPERTY()
	bool paused;

	UPROPERTY()
	APlayerController* playerController;

	class URadioSilenceGameInstance* gameInstance;
	
};
