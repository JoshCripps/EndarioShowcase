// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Player/MainPlayerController.h"
#include "GameFramework/PlayerController.h"
#include "Components/InputComponent.h"
#include "Core/Player/CameraMovementComponent.h"
#include "Core/Villager/VillagerLead.h"



AMainPlayerController::AMainPlayerController() {
		
	// Set this pawn to call Tick() every frame. (And we can turn off as needed)
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

// Begin Play
void AMainPlayerController::BeginPlay() {

	Super::BeginPlay();

	// Reference Casts
	CameraPawnRef = Cast<ACameraPawn>(GetPawn()); // Get Camera Pawn
	CameraMovementRef = CameraPawnRef->PawnMovementComponent; // Get Camera Pawn

	// Show Mouse
	bShowMouseCursor = true;

}

void AMainPlayerController::Tick(float DeltaTime) {
	
	Super::Tick(DeltaTime);
	CameraMovementRef->EdgeScroll(); // Note Could Deactivate
}

void AMainPlayerController::SetupInputComponent() {

	Super::SetupInputComponent();

	// Setup Gameplay Key Bindings
	check(InputComponent);


	// Input Events - Related to Basic Movement
	// MoveForward
	InputComponent->BindAxis("MoveForward", this, &AMainPlayerController::CallMoveForward);

	// MoveRight
	InputComponent->BindAxis("MoveRight", this, &AMainPlayerController::CallMoveRight);

	// Speed Modifier Increase (with shift down)
	InputComponent->BindAction("SpeedModifier", IE_Pressed, this, &AMainPlayerController::CallIncreaseSpeedModifier);

	// Speed Modifier Default (with shift release)
	InputComponent->BindAction("SpeedModifier", IE_Released, this, &AMainPlayerController::CallDecreaseSpeedModifier);

	// Input Events - Related to Other Movement
	// Pan Camera Left
	InputComponent->BindAction("PanCameraLeft", IE_Pressed, this, &AMainPlayerController::CallPanCameraLeft);

	// Pan Camera Right
	InputComponent->BindAction("PanCameraRight", IE_Pressed, this, &AMainPlayerController::CallPanCameraRight);

	// Pan Reset
	InputComponent->BindAction("PanReset", IE_Pressed, this, &AMainPlayerController::CallPanReset);

	// Zoom In
	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &AMainPlayerController::CallZoomIn);

	// Zoom Out
	InputComponent->BindAction("ZoomOut", IE_Pressed, this, &AMainPlayerController::CallZoomOut);

	// Zoom Reset
	InputComponent->BindAction("ResetZoom", IE_Pressed, this, &AMainPlayerController::CallZoomReset);


}	

void AMainPlayerController::CallMoveForward(float Value) {

	CameraMovementRef->BasicMovementControl(Value, 0.0);
}

void AMainPlayerController::CallMoveRight(float Value) {

	CameraMovementRef->BasicMovementControl(0.0, Value);
}

void AMainPlayerController::CallIncreaseSpeedModifier() {

	CameraMovementRef->SetMovementSpeedModifier(2.0f);
}

void AMainPlayerController::CallDecreaseSpeedModifier() {

	CameraMovementRef->SetMovementSpeedModifier(1.0f);
}

void AMainPlayerController::CallPanCameraLeft() {

	CameraMovementRef->PanCamera(45.0f);
}

void AMainPlayerController::CallPanCameraRight() {

	CameraMovementRef->PanCamera(-45.0f);
}
void AMainPlayerController::CallPanReset() {

	CameraMovementRef->ResetPan();
}

void AMainPlayerController::CallZoomIn() {

	CameraMovementRef->ZoomIn();
}

void AMainPlayerController::CallZoomOut() {

	CameraMovementRef->ZoomOut();
}

void AMainPlayerController::CallZoomReset() {

	CameraMovementRef->DefaultZoom();
}
