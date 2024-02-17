// Fill out your copyright notice in the Description page of Project Settings.


#include "Boat.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "RadioSilenceGameCharacter.h"
#include "Components/ArrowComponent.h"
#include "Logging/StructuredLog.h"
#include "DrawDebugHelpers.h"

// Sets default values
ABoat::ABoat()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoatMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoatMesh"));

	RaycastCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("RaycastCollider"));
	
	RootComponent = BoatMesh;
	RaycastCollider->SetupAttachment(BoatMesh);
}

// Called when the game starts or when spawned
void ABoat::BeginPlay()
{
	Super::BeginPlay();
	waterPosition = BoatMesh->GetRelativeLocation().Z;
	forwardMovement = 0;
	turnMovement = 0;

	isControlled = false;

	forwardVector = BoatMesh->GetForwardVector();
}

// Called every frame
void ABoat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!isControlled) {
		return;
	}

	// Forward - Backward
	if (forwardMovement != 0) {
		SetActorLocation(GetActorLocation() + forwardVector * forwardMovement * boatSpeed * DeltaTime, true);
	}

	// Rotation
	if (turnMovement != 0) {
		FRotator NewRotation = FRotator();
		NewRotation.Yaw = turnMovement * turnSpeed * DeltaTime;
		NewRotation.Roll = 0;
		NewRotation.Pitch = 0;

		BoatMesh->AddLocalRotation(NewRotation);
		//SetActorRotation(NewRotation);

		// Update forwardVector
		FRotator ForwardRotation = forwardVector.Rotation();
		ForwardRotation.Yaw += turnMovement * turnSpeed * DeltaTime;
		forwardVector = ForwardRotation.Vector();
		UE_LOGFMT(LogTemp, Log, "Yaw: {0}", ForwardRotation.Yaw);
	}
}

void ABoat::OnUsed(AController* user)
{
	UE_LOG(LogTemp, Display, TEXT("Driving Boat"));
	if (user == nullptr) return;

	ARadioSilenceGameCharacter* CurrentCharacter = Cast<ARadioSilenceGameCharacter>(user->GetCharacter());
	CurrentCharacter->EnableBoatControls(this);
}

void ABoat::DisplayPrompt(UCanvas* Canvas, AController* user)
{
}

void ABoat::Move(double forward, double right)
{
	forwardMovement = forward;
	turnMovement = right;
}

FVector ABoat::GetPlayerPosition()
{
	return BoatMesh->GetRelativeLocation() + 
		BoatMesh->GetForwardVector() *playerOffset.X + 
		BoatMesh->GetRightVector() * playerOffset.Y +
		BoatMesh->GetUpVector() * playerOffset.Z;
}

FRotator ABoat::GetPlayerRotation()
{
	return BoatMesh->GetForwardVector().Rotation();
}

void ABoat::SetIsControlled(bool value)
{
	isControlled = value;
}
