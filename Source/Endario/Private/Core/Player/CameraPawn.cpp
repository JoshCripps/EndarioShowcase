// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Player/CameraPawn.h"
#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SphereComponent.h"
#include "Camera/CameraComponent.h"
#include "Core/Player/CameraMovementComponent.h"
#include "GameFramework/Pawn.h"

// Sets default values
ACameraPawn::ACameraPawn()
{
	// Set Defaults
	DefaultZoomLength = 2500.0f;
	// DefaultZoomLength = 1350.0f;
	DefaultCameraRotation = FRotator(-45.0, 0.0, 0.0); // Pitch (y), Yaw (z), Roll (x)

	// Set Root Component and also set root comp's size.
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	SetRootComponent(CollisionSphere);
	CollisionSphere->InitSphereRadius(32.0);
	CollisionSphere->SetWorldScale3D(FVector(0.25, 0.25, 0.25));
	// TODO: Collision Profile Name for map boundaries here...
		
	// Default Settings for inheriting contorller rotations
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw   = false;
	bUseControllerRotationRoll  = false;

	// Create CameraArm and attach to root
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraArm->SetupAttachment(RootComponent);
	CameraArm->SetUsingAbsoluteRotation(false); // Rotate arm (and thus camera) when pawn rotates 
	//DEPRECATED: CameraArm->bAbsoluteRotation = false; // Rotate arm (and thus camera) when pawn rotates 
	CameraArm->TargetArmLength = DefaultZoomLength; // This is also the default Zoom Length
	CameraArm->SetRelativeRotation(DefaultCameraRotation); // Pitch (y), Yaw (z), Roll (x)
	//DEPRECATED: CameraArm->RelativeRotation = DefaultCameraRotation; // Pitch (y), Yaw (z), Roll (x)
	CameraArm->bDoCollisionTest = false; // Do not do collision test for camera arm!
	CameraArm->bEnableCameraLag = true; // Makes movements smoother
	CameraArm->bEnableCameraRotationLag = false; // Lag might be useful in preventing 'jerking' motion when zooming (or can use a lerp instead)
	CameraArm->bInheritPitch = false; // Don't want to inherit pitch or doesnt update zoom in realtime

	// Joshes
	CameraArm->CameraLagSpeed = 6.0f;
	
	// Create Camera
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);
	// TODO Set Field of View
	PlayerCamera->FieldOfView = 50;


 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	//enum temp {false, false, false, false};
	//this->AutoPossessAI = Disabled;
	//this->AutoPossessAI(false);
	//static ConstructorHelpers::FObjectFinder<UBlueprint> AICon(TEXT("Blueprint'/Game/Core/DebugAndTest/AI/TEST_UnitAIController.TEST_UnitAIController'"));
	AIControllerClass = nullptr;

	// Cheating to Prevent Circular Dependency (3)
	// Attach Movement Component
	PawnMovementComponent = CreateDefaultSubobject<UCameraMovementComponent>(TEXT("CameraPawnMovementComponent"));
}

// Called when the game starts or when spawned
void ACameraPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



// Dont need
// //Called to bind functionality to input
//void ACameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//
//}

float ACameraPawn::GetCurrentArmLength() {

	return CameraArm->TargetArmLength;
}

FRotator ACameraPawn::GetCurrentRotation() {

	return CameraArm->GetRelativeRotation();
}

// Setters
void ACameraPawn::SetArmLength(float ChangeAmount) {
		
	//FInterpCurveVector
	//CameraArm->TargetArmLength += ChangeAmount;

	// TODO: Unless you find a better method you need to hook up to tick function like in: https://answers.unrealengine.com/questions/121578/best-way-to-move-camera-smoothly.html
	CameraArm->TargetArmLength = FMath::FInterpTo(CameraArm->TargetArmLength, CameraArm->TargetArmLength+ChangeAmount, GetWorld()->GetDeltaSeconds(), 9.0f);;
	
}

void ACameraPawn::SetArmRotation(FRotator ChangeAmount) {

	// Setting our min and max rotation amounts
	const FRotator RotationMax = FRotator(-25.0, 0.0, 0.0); // Zoom in Rotation Max
	const FRotator RotationMin = DefaultCameraRotation; // Zoom out Rotation Min (revert to default)

	// Get 'x', the rotation change
	FRotator NewRotation = FRotator(CameraArm->GetRelativeRotation() + ChangeAmount);

	// Clamp the Pitch of New Rotation (using nested ternary sorry)
	NewRotation = (NewRotation.Pitch < RotationMin.Pitch) ? RotationMin : (NewRotation.Pitch < RotationMax.Pitch) ? NewRotation : RotationMax;

	CameraArm->SetRelativeRotation(NewRotation); // CameraArm->RelativeRotation

	//CameraArm->TargetArmLength += ChangeAmount;
	//CameraArm->TargetArmLength += ChangeAmount;
}

void ACameraPawn::SetToDefaultZoom() {

	CameraArm->TargetArmLength = DefaultZoomLength;
	CameraArm->SetRelativeRotation(DefaultCameraRotation);
}

