// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DirectionalLight.h"
#include "Misc/OutputDeviceNull.h"
#include "DayNightCycle.generated.h"

UCLASS()
class RADIOSILENCEGAME_API ADayNightCycle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADayNightCycle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Sky")
	AActor* sun;

	UPROPERTY(EditAnywhere, Category = "Sky")
	ADirectionalLight* lightSource;

	UPROPERTY(EditAnywhere, Category = "Sky")
	float timeSpeed;

	UPROPERTY(EditAnywhere, Category = "Sky")
	float currentTime;

	UFUNCTION()
	int GetHour();

	UFUNCTION()
	int GetMinutes();

private:
	float maxDayTime;
};
