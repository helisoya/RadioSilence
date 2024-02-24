// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MapIconWidget.generated.h"


class UCanvasPanelSlot;

/**
 * 
 */
UCLASS()
class RADIOSILENCEGAME_API UMapIconWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* image;


	/** Initialize the Widget **/
	void Init(UTexture2D* texture);

	/** Changes the position of the image **/
	void SetPosition(FVector2D position);

	/** Changes the slot of the icon **/
	void SetSlot(UCanvasPanelSlot* newSlot);


private :

	UPROPERTY()
	UCanvasPanelSlot* canvasSlot;

};
