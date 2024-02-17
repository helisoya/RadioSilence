// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Usable.generated.h"


/**This interface has to be added to every Actor that can be used, you have to implement the OnUsed function */
UINTERFACE(MinimalAPI)
class UUsable :public UInterface
{
	GENERATED_BODY()
};

class IUsable
{
	GENERATED_BODY()

public:
	// This function will be called when the user uses the object
	virtual void OnUsed(AController* user);
	// This function is called each frame from the hud, it should be used to put messages to the screen, like the USE promt in UDK
	virtual void DisplayPrompt(UCanvas* Canvas, AController* user);
};