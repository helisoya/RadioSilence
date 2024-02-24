// Copyright Epic Games, Inc. All Rights Reserved.

#include "RadioSilenceGameCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PhysicsVolume.h"
#include "Usable.h"
#include "CollisionQueryParams.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/EngineTypes.h"
#include "Boat.h"
#include "RadioSilenceGUI.h"
#include "Blueprint/UserWidget.h"
#include "RadioSilenceGamePlayerController.h"
#include "MapIconWidget.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ARadioSilenceGameCharacter

ARadioSilenceGameCharacter::ARadioSilenceGameCharacter()
{	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	PlayerGUIClass = nullptr;
	PlayerGUI = nullptr;

}

void ARadioSilenceGameCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>(Controller);

	// Add Input Mapping Context
	if (PlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	if (PlayerGUIClass) {
		ARadioSilenceGamePlayerController* controller = GetController<ARadioSilenceGamePlayerController>();
		check(controller);
		UE_LOG(LogTemp, Display, TEXT("Controller OK"));
		PlayerGUI = CreateWidget<URadioSilenceGUI>(controller, PlayerGUIClass);
		check(PlayerGUI);
		UE_LOG(LogTemp, Display, TEXT("GUI OK"));
		PlayerGUI->AddToViewport();

		PlayerGUI->Init(PlayerController);
		
		if (MapIconWidgetClass) {
			mapIcon = CreateWidget<UMapIconWidget>(controller, MapIconWidgetClass);
			check(mapIcon);
			UE_LOG(LogTemp, Display, TEXT("Icon OK"));

			mapIcon->Init(iconTexture);
			PlayerGUI->AddIconToMap(mapIcon);
		}
	}

}

void ARadioSilenceGameCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (PlayerGUI) {
		PlayerGUI->RemoveFromParent();
		PlayerGUI = nullptr;
	}
}

//////////////////////////////////////////////////////////////////////////// Input

void ARadioSilenceGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARadioSilenceGameCharacter::Move);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &ARadioSilenceGameCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ARadioSilenceGameCharacter::Look);

		// Running 
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Started, this, &ARadioSilenceGameCharacter::StartRun);
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Completed, this, &ARadioSilenceGameCharacter::EndRun);

		// Pause
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Triggered, this, &ARadioSilenceGameCharacter::PauseGame);

		// Interaction
		EnhancedInputComponent->BindAction(InteractionAction, ETriggerEvent::Triggered, this, &ARadioSilenceGameCharacter::Interaction);

		//this->GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ARadioSilenceGameCharacter::EnableBoatControls(ABoat* boat)
{
	boatControlling = boat;
	boatControlling->SetIsControlled(true);
	this->SetActorEnableCollision(false);
}

void ARadioSilenceGameCharacter::DisableBoatControls()
{
	boatControlling->SetIsControlled(false);
	boatControlling = nullptr;
	this->SetActorEnableCollision(true);
}


void ARadioSilenceGameCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (boatControlling != nullptr) {
		boatControlling->Move(MovementVector.Y, MovementVector.X);
	}
	else if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void ARadioSilenceGameCharacter::Look(const FInputActionValue& Value)
{
	if (boatControlling != nullptr) return;

	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ARadioSilenceGameCharacter::StartRun(const FInputActionValue& Value)
{
	if (boatControlling != nullptr) return;

	if (Controller != nullptr)
	{
		this->GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
	}
}

void ARadioSilenceGameCharacter::EndRun(const FInputActionValue& Value)
{
	if (boatControlling != nullptr) return;

	if (Controller != nullptr)
	{
		this->GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}
}

void ARadioSilenceGameCharacter::PauseGame(const FInputActionValue& Value)
{
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller)) {


		if (PlayerGUI->IsPaused()) {
			PlayerGUI->ClosePauseMenu();
		}
		else {
			PlayerGUI->OpenPauseMenu();
		}
		
	}
}

void ARadioSilenceGameCharacter::Interaction(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Display, TEXT("Interacting"));

	if (boatControlling != nullptr) {
		DisableBoatControls();
	}
	else if (UseFocus != nullptr) {
		UseFocus->OnUsed(GetController());
	}
}

void ARadioSilenceGameCharacter::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);

	// Updating Map Icon

	FVector2D mapPos;
	FVector playerPos = GetActorLocation();

	mapIcon->SetPosition(FVector2D(
		playerPos.X / 806400 * 1000 - 15,
		playerPos.Y / 806400 * 1000 - 15));

	if (boatControlling == nullptr && Controller && Controller->IsLocalPlayerController()) // we check the controller becouse we dont want bots to grab the use object and we need a controller for the Getplayerviewpoint function
	{
		FVector CamLoc;
		FRotator CamRot;


		Controller->GetPlayerViewPoint(CamLoc, CamRot); // Get the camera position and rotation
		const FVector StartTrace = CamLoc; // trace start is the camera location
		const FVector Direction = CamRot.Vector();
		const FVector EndTrace = StartTrace + Direction * maxInteractionDistance; // and trace end is the camera location + an offset in the direction you are looking, the 200 is the distance at wich it checks

		UseFocus = nullptr;
		FHitResult Hit(ForceInit);
		if (GetWorld()->LineTraceSingleByChannel(Hit, StartTrace, EndTrace, ECC_GameTraceChannel2)) {
			IUsable* usable = Cast<IUsable>(Hit.GetActor()); // we cast the hit actor to the IUsable interface
			
			if (usable) 
			{
				UE_LOG(LogTemp, Display, TEXT("Seeing usable object"));
				UseFocus = usable;
			}
		}

		if (UseFocus) {
			UseFocus->DisplayPrompt(PlayerGUI);
		}
		else {
			PlayerGUI->SetInteractionText("");
		}
	}
	else {
		SetActorLocation(boatControlling->GetPlayerPosition());
		//FirstPersonCameraComponent->SetRelativeRotation(boatControlling->GetPlayerRotation());
		Controller->ClientSetRotation(boatControlling->GetPlayerRotation()); // here
		return;
	}

	float posZ = this->GetActorLocation().Z;

	if (swimming && posZ > waterHeight) {
		ChangeSwimming(false);
	}
	else if (!swimming && posZ < waterHeight) {
		ChangeSwimming(true);
	}
}

void ARadioSilenceGameCharacter::ChangeSwimming(bool isSwimming)
{
	swimming = isSwimming;
	this->GetCharacterMovement()->SetMovementMode(swimming ?
		this->GetCharacterMovement()->DefaultWaterMovementMode.GetValue() :
		this->GetCharacterMovement()->DefaultLandMovementMode.GetValue()
	);

	this->GetPhysicsVolume()->bWaterVolume = swimming;
}