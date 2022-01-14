// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Player/CameraMovementComponent.h"
#include "Core/Player/CameraPawn.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

// Sets default values for this component's properties
UCameraMovementComponent::UCameraMovementComponent() {

	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;

	// Set Default Attributes
	bDisableCameraMovement = false;
	DefaultMovementSpeed = 15.0;
	MovementSpeedModifier = 1.0;
	DefaultZoomLength = 2500.0;
	// DefaultZoomLength = 1350.0;
	DeltaArm = 75.0;
	DeltaRotation = FRotator(7.15, 0.0, 0.0);
	MaxZoom = 100.0; // Closest Camera can get to the Map
	MinZoom = 2000.0; // Furthest Camera can get away from the Map
}

// Called when the game starts
void UCameraMovementComponent::BeginPlay() {
	Super::BeginPlay();

	// Cast to the owner
	CameraOwner = Cast<ACameraPawn>(GetOwner()); // Populates the owner of this component.
	PlayerControllerRef = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)); // Populates Player Controller Ref
}

// Called every frame
void UCameraMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

// Getters
FVector UCameraMovementComponent::GetCameraLocation() {
	return CameraOwner->GetActorLocation();
}

FVector UCameraMovementComponent::GetFaceDirection() {
	return CameraOwner->GetActorForwardVector();
}

FRotator UCameraMovementComponent::GetCameraRotation() {
	return CameraOwner->GetActorRotation();
}

// Setters
float UCameraMovementComponent::SetMovementSpeedModifier(float ModifierAmount) {
	return MovementSpeedModifier = ModifierAmount;
}

float UCameraMovementComponent::SetMovememtSpeed(float MovementSpeedAdjustment) {
	return DefaultMovementSpeed = MovementSpeedAdjustment;
}

bool UCameraMovementComponent::SetCameraDisable(bool bDisableCamera) {
	return bDisableCameraMovement = bDisableCamera;
}

// Utilities: Basic Movement Controls
void UCameraMovementComponent::BasicMovementControl(float AxisValueX, float AxisValueY) {

	float MovementValueX;
	float MovementValueY;
	FVector MovementX;
	FVector MovementY;

	if (!IsCameraDisable()) {

		// Diagonals First
		if (AxisValueX != 0 && AxisValueY != 0) {
			MovementValueX = AxisValueX * GetCurrentMovementSpeed() * GetSpeedModifier();
			MovementX = FVector(MovementValueX, 0.0f, 0.0f);

			MovementValueY =  AxisValueY * GetCurrentMovementSpeed() * GetSpeedModifier();
			MovementY = FVector(0.0f, MovementValueY, 0.0f);

			CameraOwner->AddActorLocalOffset(MovementX + MovementY, true);
		}
		else if (AxisValueX != 0) {
			MovementValueX = AxisValueX * GetCurrentMovementSpeed() * GetSpeedModifier();
			MovementX = FVector(MovementValueX, 0.0f, 0.0f);

			CameraOwner->AddActorLocalOffset(MovementX, true);
		}
		else if (AxisValueY != 0) {
			MovementValueY = AxisValueY * GetCurrentMovementSpeed() * GetSpeedModifier();
			MovementY = FVector(0.0f, MovementValueY, 0.0f);

			CameraOwner->AddActorLocalOffset(MovementY, true);
		}
	}
}

/** Camera Pan */
void UCameraMovementComponent::PanCamera(float RotationAmount) {

	FRotator NewRotation = GetCameraRotation().Add(0, RotationAmount, 0);
	CameraOwner->SetActorRotation(NewRotation);
}

/** Resets Camera Pan/Rotation */
void UCameraMovementComponent::ResetPan() {

	CameraOwner->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
}


/** Edge Scroll - X and Y are reversed on screen from Game World */
void UCameraMovementComponent::EdgeScroll() {

	// Variables for movement
	float DeltaSpeedX;
	float DeltaSpeedY;
	FVector MovementX;
	FVector MovementY;

	// Get Mouse Position
	float MousePositionX{ 0 };
	float MousePositionY{ 0 };
	PlayerControllerRef->GetMousePosition(MousePositionX, MousePositionY); // Pass by Reference

	// Get Viewport (Play Screen) size
	int32 ViewportSizeX;
	int32 ViewportSizeY;
	PlayerControllerRef->GetViewportSize(ViewportSizeX, ViewportSizeY);

	// Calculate Proportions (We want these calculations to be updated with the mouses movement
	float ProportionX = MousePositionX / ViewportSizeX;
	float ProportionY = MousePositionY / ViewportSizeY;

	// Set EdgeScrollSpeeds based on Proportion
	if (ProportionX >= 0.975f && ProportionY <= 0.025f) {

		DeltaSpeedX = 7.07f * GetSpeedModifier();
		DeltaSpeedY = 7.07f;

		MovementX = FVector(DeltaSpeedY, 0.0f, 0.0f);
		MovementY = FVector(0.0f, DeltaSpeedX, 0.0f);

		CameraOwner->AddActorLocalOffset(MovementX + MovementY, true);
	}
	else if (ProportionX >= 0.975f && ProportionY >= 0.975f) {
		// Bottom Right Corner
		SetCameraDisable(true); // Disable WASD Keys
		DeltaSpeedX = 7.07f * GetSpeedModifier();
		DeltaSpeedY = -7.07f;

		MovementX = FVector(DeltaSpeedY, 0.0f, 0.0f);
		MovementY = FVector(0.0f, DeltaSpeedX, 0.0f);

		CameraOwner->AddActorLocalOffset(MovementX + MovementY, true);
		SetCameraDisable(true); // Disable WASD Keys
	}
	else if (ProportionX <= 0.025f && ProportionY <= 0.025f) {
		// Top Left Corner
		DeltaSpeedX = -7.07f * GetSpeedModifier();
		DeltaSpeedY = 7.07f;

		MovementX = FVector(DeltaSpeedY, 0.0f, 0.0f);
		MovementY = FVector(0.0f, DeltaSpeedX, 0.0f);

		CameraOwner->AddActorLocalOffset(MovementX + MovementY, true);
		SetCameraDisable(true); // Disable WASD Keys
	}
	else if (ProportionX <= 0.025f && ProportionY >= 0.975f) {
		// Top Right Corner
		DeltaSpeedX = -7.07f * GetSpeedModifier();
		DeltaSpeedY = -7.07f;

		MovementX = FVector(DeltaSpeedY, 0.0f, 0.0f);
		MovementY = FVector(0.0f, DeltaSpeedX, 0.0f);

		CameraOwner->AddActorLocalOffset(MovementX + MovementY, true);
		SetCameraDisable(true); // Disable WASD Keys
	}
	else if (ProportionX >= 0.975f) {
		// Right Side
		DeltaSpeedX = 10.0 * GetSpeedModifier();
		DeltaSpeedY = 0;

		MovementY = FVector(0.0f, DeltaSpeedX, 0.0f);

		CameraOwner->AddActorLocalOffset(MovementY, true);
		SetCameraDisable(true); // Disable WASD Keys
	}
	else if (ProportionX <= 0.25f) {
		// Left Side
		DeltaSpeedX = -10.0 * GetSpeedModifier();
		DeltaSpeedY = 0;

		MovementY = FVector(0.0f, DeltaSpeedX, 0.0f);

		CameraOwner->AddActorLocalOffset(MovementY, true);
		SetCameraDisable(true); // Disable WASD Keys
	}
	else if (ProportionY >= 0.975f) {
		// Bottom Side
		DeltaSpeedX = 0.0;
		DeltaSpeedY = -10.0f * GetSpeedModifier();

		MovementY = FVector(DeltaSpeedY, 0.0f, 0.0f);

		CameraOwner->AddActorLocalOffset(MovementY, true);
		SetCameraDisable(true); // Disable WASD Keys
	}
	else if (ProportionY <= 0.025f) {
		// Top Side
		DeltaSpeedX = 0.0;
		DeltaSpeedY = 10.0f * GetSpeedModifier();

		MovementY = FVector(DeltaSpeedY, 0.0f, 0.0f);

		CameraOwner->AddActorLocalOffset(MovementY, true);
		SetCameraDisable(true); // Disable WASD Keys
	}
	else {
		DeltaSpeedX = 0.0;
		DeltaSpeedY = 0.0;

		SetCameraDisable(false);
	}
}

/** Zoom In */
void UCameraMovementComponent::ZoomIn() {

	UE_LOG(LogTemp, Warning, TEXT("Zooming In: %f"), CameraOwner->GetCurrentArmLength());
	if (CameraOwner->GetCurrentArmLength() >= MaxZoom) {
		CameraOwner->SetArmLength(-100.0f * DeltaArm);
	}
}

/** Zoom Out */
void UCameraMovementComponent::ZoomOut() {

	UE_LOG(LogTemp, Warning, TEXT("Zooming Out: %f"), CameraOwner->GetCurrentArmLength());
	if (CameraOwner->GetCurrentArmLength() <= MinZoom) {
		CameraOwner->SetArmLength(DeltaArm);
	}
}

/** Zoom Reset */
void UCameraMovementComponent::DefaultZoom() {

	CameraOwner->SetToDefaultZoom();
}
