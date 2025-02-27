// Fill out your copyright notice in the Description page of Project Settings.


#include "DayNightCycle.h"
#include "RadioSilenceGameInstance.h"

// Sets default values
ADayNightCycle::ADayNightCycle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	maxDayTime = 24 * 60;
}

// Called when the game starts or when spawned
void ADayNightCycle::BeginPlay()
{
	Super::BeginPlay();

	URadioSilenceGameInstance* gameInstance = Cast<URadioSilenceGameInstance>(GetGameInstance());
	if (gameInstance) {
		gameInstance->dayNightCycle = this;
	}
}

// Called every frame
void ADayNightCycle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	currentTime += DeltaTime * timeSpeed;
	if (currentTime >= maxDayTime) {
		currentTime -= maxDayTime;
	}

	if (lightSource) {
		lightSource->SetActorRelativeRotation(FRotator(
			180 + 180 * ((float)GetHour() / (float)24),
			0,
			0
		));
		//lightSource->AddActorLocalRotation(FRotator(DeltaTime * timeSpeed), 0, 0);
	}

	if (sun) {
		FOutputDeviceNull ar;
		sun->CallFunctionByNameWithArguments(TEXT("UpdateSunDirection"), ar, NULL, true);
	}
}

int ADayNightCycle::GetHour()
{
	return  FMath::Floor(currentTime / 60);
}

int ADayNightCycle::GetMinutes()
{
	return (int)currentTime % 60;
}

