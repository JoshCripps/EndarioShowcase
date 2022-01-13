// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CameraPawn.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ENDARIO_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()


public:

	// Constructor
	AMainPlayerController();

protected:
	// Begin Play
	virtual void BeginPlay() override;


public:
	// -- -- -- -- - -- -- -- -- --
	// -- -- -- ATTRIBUTES -- -- --
	
	// - - - - -  CAMERA  - - - - -

	/** Reference to Camera Pawn */
	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite)
	ACameraPawn* CameraPawnRef;

	/** Reference to Camera Movement Component */
	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite)
	UCameraMovementComponent* CameraMovementRef;


	// - - - - - VILLAGER - - - - -

	/** Reference to Villager Lead Component */
	// -- TODO ADD CODE HERE? --
	//UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite)
	//UCameraMovementComponent* CameraMovementRef;


	// -- -- -- -- -- -- -- -- -- --
	// -- -- -- - METHODS - -- -- --
	// -- -- -- -- -- -- -- -- -- --

	// - - - - -  CAMERA  - - - - -

	// Tick Function
	virtual void Tick(float DeltaTime) override;

	// Connect to Controller
	virtual void SetupInputComponent() override;


	// Move Forward Controls 'W' or 'S'
	virtual void CallMoveForward(float Value);

	// Move Right Controls 'A' or 'D'
	virtual void CallMoveRight(float Value);

	// Increase Speed Modifier 'Shft Down'
	virtual void CallIncreaseSpeedModifier();

	// Increase Speed Modifier 'Shft Up'
	virtual void CallDecreaseSpeedModifier();

	// Camera Rotate Left by 45 deg
	virtual void CallPanCameraLeft();

	// Camera Rotate Right by 45 deg
	virtual void CallPanCameraRight();

	// Camera Rotate Reset 
	virtual void CallPanReset();

	// Camera Zoom In
	virtual void CallZoomIn();

	// Camera Zoom Out
	virtual void CallZoomOut();

	// Camera Zoom Reset 
	virtual void CallZoomReset();

	// - - - - VILLAGER - - - -
};


