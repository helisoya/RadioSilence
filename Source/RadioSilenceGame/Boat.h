// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Usable.h"
#include "Boat.generated.h"



class UStaticMeshComponent;
class UBuoyancyComponent;
class UBoxComponent;
class URadioSilenceGUI;
class UInputComponent;



UCLASS()
class RADIOSILENCEGAME_API ABoat : public APawn, public IUsable
{
	GENERATED_BODY()

	/** Boat Mesh */
	UPROPERTY(VisibleAnywhere, Category = Mesh)
	UStaticMeshComponent* BoatMesh;

	/** Raycast Collider */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	UBoxComponent* RaycastCollider;

	/** Boat Speed */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Infos, meta = (AllowPrivateAccess = "true"))
	float boatSpeed;

	/** Turn Speed */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Infos, meta = (AllowPrivateAccess = "true"))
	float turnSpeed;

	/** Player Offset */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Infos, meta = (AllowPrivateAccess = "true"))
	FVector playerOffset;

	float waterPosition;
	double forwardMovement;
	double turnMovement;
	FVector forwardVector;

	bool isControlled;


public:
	// Sets default values for this actor's properties
	ABoat();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// This function will be called when the user uses the object
	virtual void OnUsed(AController* user) override;
	// This function is called each frame from the hud, it should be used to put messages to the screen, like the USE promt in UDK
	virtual void DisplayPrompt(URadioSilenceGUI* gui) override;

	void Move(double forward, double right);

	FVector GetPlayerPosition();

	FRotator GetPlayerRotation();

	void SetIsControlled(bool value);

};