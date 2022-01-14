// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Player/MainPlayerController.h"
#include "GameFramework/PlayerController.h"
#include "Components/InputComponent.h"
#include "Core/Player/CameraMovementComponent.h"
#include "Core/Villager/VillagerLead.h"

AMainPlayerController::AMainPlayerController() {

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
	CameraMovementRef->EdgeScroll();
}

void AMainPlayerController::SetupInputComponent() {

	Super::SetupInputComponent();

	// Setup Gameplay Key Bindings
	check(InputComponent);

	InputComponent->BindAxis("MoveForward", this, &AMainPlayerController::CallMoveForward);

	InputComponent->BindAxis("MoveRight", this, &AMainPlayerController::CallMoveRight);

	InputComponent->BindAction("SpeedModifier", IE_Pressed, this, &AMainPlayerController::CallIncreaseSpeedModifier);

	InputComponent->BindAction("SpeedModifier", IE_Released, this, &AMainPlayerController::CallDecreaseSpeedModifier);

	InputComponent->BindAction("PanCameraLeft", IE_Pressed, this, &AMainPlayerController::CallPanCameraLeft);

	InputComponent->BindAction("PanCameraRight", IE_Pressed, this, &AMainPlayerController::CallPanCameraRight);

	InputComponent->BindAction("PanReset", IE_Pressed, this, &AMainPlayerController::CallPanReset);

	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &AMainPlayerController::CallZoomIn);

	InputComponent->BindAction("ZoomOut", IE_Pressed, this, &AMainPlayerController::CallZoomOut);

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
