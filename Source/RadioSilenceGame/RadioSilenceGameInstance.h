// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RadioSilenceGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class RADIOSILENCEGAME_API URadioSilenceGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY()
	class ADayNightCycle* dayNightCycle;

	class URadioSilenceGUI* gui;

};
