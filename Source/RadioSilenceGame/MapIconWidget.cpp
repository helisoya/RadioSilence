// Fill out your copyright notice in the Description page of Project Settings.


#include "MapIconWidget.h"
#include "Components/Image.h"
#include "Logging/StructuredLog.h"
#include "Components/CanvasPanelSlot.h"

void UMapIconWidget::Init(UTexture2D* texture)
{
	image->SetBrushFromTexture(texture);
	image->SetBrushSize(FVector2D(30, 30));
}

void UMapIconWidget::SetPosition(FVector2D position)
{
	if (canvasSlot) {
		canvasSlot->SetPosition(position);
	}
	
	// Real Map Size = 806400 x 806400
}

void UMapIconWidget::SetSlot(UCanvasPanelSlot* newSlot)
{
	canvasSlot = newSlot;
	if (canvasSlot) {
		canvasSlot->SetSize(FVector2D(30, 30));
	}
}
