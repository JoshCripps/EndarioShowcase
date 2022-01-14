// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Pawn.h"
#include "CameraPawn.generated.h"

// Cheating to Prevent Circular Dependency (1)
class UCameraMovementComponent;

UCLASS()
class ENDARIO_API ACameraPawn : public APawn {
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACameraPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// Camera Movement Component declaration will go here
	// Circular Dependency Prevention
	UPROPERTY(Category = "Movement Component", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraMovementComponent* PawnMovementComponent;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

// Attributes
protected:
	/**  Collision spehere and root component */
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Root Comp")
	class USphereComponent* CollisionSphere;

	/** Player Camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Camera")
	class UCameraComponent* PlayerCamera;

	/** SpringArm or CameraArm */
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Camera")
	class USpringArmComponent* CameraArm;

	/** Default CameraArm Length */
	UPROPERTY(Category = "Movement Variables: Zoom", BlueprintReadonly)
	float DefaultZoomLength;

	/** Default Rotation */
	UPROPERTY(Category = "Movement Variables: Zoom", BlueprintReadonly)
	FRotator DefaultCameraRotation;
public:

	// Getters
	/** Returns Camera */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Getters")
	FORCEINLINE class UCameraComponent* GetCamera() const { return PlayerCamera; }

	/** Returns Camera */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Getters")
	FORCEINLINE class USpringArmComponent* GetCameraArm() const { return CameraArm; }

	/** Returns Length of CameraArm */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Camera Zoom")
	float GetCurrentArmLength();

	/** Returns Rotation of CameraArm */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Camera Zoom")
	FRotator GetCurrentRotation();

	// Setters
	UFUNCTION(BlueprintCallable, Category = "Camera Zoom")
	virtual void SetArmLength(float ChangeAmount);

	UFUNCTION(BlueprintCallable, Category = "Camera Zoom")
	virtual void SetArmRotation(FRotator ChangeAmount);

	UFUNCTION(BlueprintCallable, Category = "Camera Zoom")
	virtual void SetToDefaultZoom();
};
