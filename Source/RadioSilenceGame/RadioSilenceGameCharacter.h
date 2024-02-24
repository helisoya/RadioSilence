// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Usable.h"
#include "RadioSilenceGameCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;
class ABoat;
class URadioSilenceGUI;
class UMapIconWidget;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ARadioSilenceGameCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Run Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* RunAction;

	/** Interaction Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractionAction;

	/** Pause Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PauseAction;


	/** Walk Speed */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Infos, meta = (AllowPrivateAccess = "true"))
	float WalkSpeed;

	/** Run Speed */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Infos, meta = (AllowPrivateAccess = "true"))
	float RunSpeed;

	/** Water Height */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Infos, meta = (AllowPrivateAccess = "true"))
	float waterHeight;

	/** Max Interaction Distance */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Infos, meta = (AllowPrivateAccess = "true"))
	int maxInteractionDistance;

	ABoat* boatControlling;
	
public:
	ARadioSilenceGameCharacter();

protected:
	virtual void BeginPlay();
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
		
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** Smimming */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Infos)
	bool swimming;

	IUsable* UseFocus;

	UPROPERTY(EditAnywhere)
	TSubclassOf<URadioSilenceGUI> PlayerGUIClass;

	UPROPERTY()
	URadioSilenceGUI* PlayerGUI;

	UPROPERTY(EditAnywhere, Category = Infos)
	TSubclassOf<UMapIconWidget> MapIconWidgetClass;

	UPROPERTY(EditAnywhere, Category = Infos)
	UTexture2D* iconTexture;

	UPROPERTY()
	UMapIconWidget* mapIcon;

protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Start Running */
	void StartRun(const FInputActionValue& Value);

	/** Start Running */
	void EndRun(const FInputActionValue& Value);

	/** Pause the Game */
	void PauseGame(const FInputActionValue& Value);

	/** Interact with objects */
	void Interaction(const FInputActionValue& Value);

	/** Tick function **/
	virtual void Tick(float deltaSeconds) override;

	/** Change if swimming **/
	void ChangeSwimming(bool isSwimming);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	void EnableBoatControls(ABoat* boat);
	void DisableBoatControls();

};

