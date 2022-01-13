// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Core/Player/CameraPawn.h"
#include "CameraMovementComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ENDARIO_API UCameraMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCameraMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** Get Attached Pawn */
	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite)
	ACameraPawn* CameraOwner;

	/** Character Controller Reference */
	UPROPERTY(BlueprintReadWrite)
	APlayerController* PlayerControllerRef;


protected:
	// Attributes

	// Bools
	/** Is Movement Disabled? */
	UPROPERTY(Category = "Movement Variables: Bools", BlueprintReadOnly)
	bool bDisableCameraMovement;


	// Movement Speeds
	/** How Fast the Camera Moves */
	UPROPERTY(Category = "Movement Variables: Movement Speeds", BlueprintReadOnly)
	float DefaultMovementSpeed;

	/** Modifies the default movemnet speed when called */
	UPROPERTY(Category = "Movement Variables: Movement Speeds", BlueprintReadOnly)
	float MovementSpeedModifier;


	// Camera Direction
	/** Gets Forward Direction of Camera Pawn */
	UPROPERTY(Category = "Movement Variables: Movement Speeds", BlueprintReadOnly)
	FVector FaceDirection;

	// Zoom
	/** Default CameraArm Length */
	UPROPERTY(Category = "Movement Variables: Zoom", BlueprintReadOnly)
	float DefaultZoomLength;

	/** Amount Camera Arm Changes */
	UPROPERTY(Category = "Movement Variables: Zoom", BlueprintReadOnly)
	float DeltaArm;
	
	/** Amount the Rotation Changes */
	UPROPERTY(Category = "Movement Variables: Zoom", BlueprintReadOnly)
	FRotator DeltaRotation;
	
	// Field of View Here

	/** Farthest Camera can get on Zoom Out */
	UPROPERTY(Category = "Movement Variables: Zoom", BlueprintReadOnly)
	float MaxZoom;

	/** Closest Camera can get on Zoom In */
	UPROPERTY(Category = "Movement Variables: Zoom", BlueprintReadOnly)
	float MinZoom;

public:
	// Methods

	// Getters
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Camera Speed")
	FORCEINLINE float GetCurrentMovementSpeed() { return DefaultMovementSpeed; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Camera Speed")
	FORCEINLINE float GetSpeedModifier() { return MovementSpeedModifier; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Camera Speed")
	FORCEINLINE bool IsCameraDisable() { return bDisableCameraMovement; }

	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Camera Location")
	FVector GetCameraLocation();
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Camera Direction")
	FVector GetFaceDirection();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Camera Direction")
	FRotator GetCameraRotation();


	// Setters
	UFUNCTION(BlueprintCallable, Category = "Camera Speed")
	float SetMovementSpeedModifier(float ModifierAmount);

	UFUNCTION(BlueprintCallable, Category = "Camera Speed")
	float SetMovememtSpeed(float MovementSpeedAdjustment);

	UFUNCTION(BlueprintCallable, Category = "Camera Speed")
	bool SetCameraDisable(bool bDisableCamera);

	// Utility
	UFUNCTION(BlueprintCallable, Category = "Camera Movement")
	virtual void BasicMovementControl(float AxisValueX, float AxisValueY);

	UFUNCTION(BlueprintCallable, Category = "Camera Movement")
	virtual void PanCamera(float RotationAmount);

	UFUNCTION(BlueprintCallable, Category = "Camera Movement")
	virtual void ResetPan();

	UFUNCTION(BlueprintCallable, Category = "Camera Movement")
	virtual void EdgeScroll();

	UFUNCTION(BlueprintCallable, Category = "Camera Zoom")
	virtual void ZoomIn();
		
	UFUNCTION(BlueprintCallable, Category = "Camera Zoom")
	virtual void ZoomOut();

	UFUNCTION(BlueprintCallable, Category = "Camera Zoom")
	virtual void DefaultZoom();
	
};
