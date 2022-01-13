// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Villager/VillagerLead.h"
#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Core/Villager/VillagerComponent.h"
#include "GameFramework/Pawn.h"
#include <time.h>



// Sets default values
AVillagerLead::AVillagerLead()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// More Temporary Mesh Things
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Villager Base Mesh"));
	SetRootComponent(BaseMesh);

	// Find and Assign Mesh
	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Models/Villagers/Temporary/VillagerMesh.VillagerMesh'"));
	if (MeshAsset.Object != nullptr)
	{
		BaseMesh->SetStaticMesh(MeshAsset.Object);
	}

	SelectionMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Villager Selection Mesh"));
	//UStaticMeshComponent* SelectionMesh;

	// Find and Assign Mesh
	auto MeshAsset2 = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Models/Decals/SelectedCube.SelectedCube'"));
	if (MeshAsset2.Object != nullptr)
	{
		SelectionMesh->SetWorldScale3D(FVector(0.02f, 0.02f, 0.01f));
		SelectionMesh->SetStaticMesh(MeshAsset2.Object);

		SelectionMesh->SetupAttachment(BaseMesh);

		SelectionMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 7.0f));
		SelectionMesh->SetVisibility(false);	
		
	}


	// Connect AI Controller
	//auto CustomAIController = ConstructorHelpers::FObjectFinder<AController>(TEXT("Blueprint'/Game/Core/DebugAndTest/TEST_AIController.TEST_AIController'"));

	static ConstructorHelpers::FObjectFinder<UBlueprint> AICon(TEXT("Blueprint'/Game/Core/DebugAndTest/AI/TEST_UnitAIController.TEST_UnitAIController'"));
	AIControllerClass = AICon.Object->GeneratedClass;
	//this->AIControllerClass = AIControllerClass::StaticClass();
	
	//getaicontroll
	//Blueprint'/Game/Core/DebugAndTest/TEST_AIController.TEST_AIController'


	// Details
	Name = "Joshua Cripps";
	Class = "Lumberjack";
	Sex = "Male";
	Mood = "Happy";
	Strength = FMath::RandRange(1, 10);
	Ocean = InitOceanDetails();


	// Set up Random Values for Ocean Personality
	//= FMath::RandRange(1, 10);
	



	// Attach Villager Component : Preventing Circular Dependency (3)
	VillagerActionsComponent = CreateDefaultSubobject<UVillagerComponent>(TEXT("LeadVillagerActionsComponent"));
}

// Called when the game starts or when spawned
void AVillagerLead::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Im called at the start: Pawn"));

	//GetStats();

	//SelectionMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	
}

// Called every frame
void AVillagerLead::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//// Called to bind functionality to input
//void AVillagerLead::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//
//}

FUnitDetailsBU AVillagerLead::GetStatsBU() {

	
	// UE_LOG(LogTemp, Warning, TEXT("Attempting to get stats: Pawn"));
	FUnitDetailsBU CurrentDetails;
	//srand(time(NULL));
	

	CurrentDetails.UnitName = Name;
	CurrentDetails.UnitGender = Sex;
	CurrentDetails.UnitMood = Mood;
	CurrentDetails.UnitClass = Class;
	CurrentDetails.UnitStrength = Strength;

	CurrentDetails.UnitOcean = Ocean;

	//SelectionMesh->SetVisibility(true);
	//CurrentDetails.UnitClass = iSecret;
	 //UE_LOG(LogTemp, Warning, TEXT("Attempting to get stats: [%s]"), *FString(iSecret) );

	//CurrentDetails.UnitName = "David Temp";
	//CurrentDetails.UnitGender = "Woman Temp";
	//CurrentDetails.UnitMood = "Hungry Temp";
	//CurrentDetails.UnitClass = "Class Temp";
	//CurrentDetails.UnitTemp = "Temp Temp";
	//CurrentDetails.UnitClass = iSecret;

	//UE_LOG(LogTemp, Warning, TEXT("Unit Details: %s, %s, %s, %s, %d"), *FString(CurrentDetails.UnitName), *FString(CurrentDetails.UnitGender), *FString(CurrentDetails.UnitMood), *FString(CurrentDetails.UnitClass), CurrentDetails.UnitStrength);


	return CurrentDetails;
}

void AVillagerLead::ToggleSelection(bool bIsSelected) {

	if (bIsSelected) {
		SelectionMesh->SetVisibility(true);

	}
	else {

		SelectionMesh->SetVisibility(false);
	}

}


TArray<int> AVillagerLead::InitOceanDetails() {


	Ocean = { 0, 1, 2, 3, 4 };

	TArray<float> tempOcean = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };

	float sumOcean = 0.0f;
	bool bBalanceFound = false;
	int32 numTries = 0;

	int32 indexesCorrect = 0;
	int32 balanceCorrect = 0;

	while (!bBalanceFound && numTries < 5) {

		sumOcean = 0;

		for (size_t i = 0; i < 5; i++) {

			// Random values between 0 and 1.
			tempOcean[i] = FMath::RandRange(0.0f, 1.0f);
			sumOcean += tempOcean[i];
		}

		indexesCorrect = 0;
		balanceCorrect = 0;
		for (size_t i = 0; i < 5; i++) {

			// Correctly Modify within range
			tempOcean[i] /= sumOcean;
			tempOcean[i] *= 25;

			Ocean[i] = FMath::RoundHalfFromZero(tempOcean[i]);

			if (tempOcean[i] < 10.0f) {
				indexesCorrect += 1;
			}
			balanceCorrect += Ocean[i];

		}

		if (indexesCorrect >= 5) {
			bBalanceFound = true;
		}
		else {
			numTries += 1;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Created Pawn with Ocean Algo %d tries"), numTries);
	UE_LOG(LogTemp, Warning, TEXT("Cur %d, %d, %d, %d, %d = %d"), Ocean[0], Ocean[1], Ocean[2], Ocean[3], Ocean[4], balanceCorrect);

	// Add Sifting if necessary TODO: More sifting will occur at top due using < not <=.... Perhaps shuffle array order?
	if (balanceCorrect < 25) {
		UE_LOG(LogTemp, Warning, TEXT("Sifting for UnderBalance"));
		int32 remainderSift = 25 - balanceCorrect;
		int32 lowestValue;
		int32 lowestIndex = 4;

		for (size_t i = 0; i < remainderSift; i++) {

			lowestValue = 100;
			lowestIndex = 4;
			for (size_t j = 0; j < 5; j++) {
				if (Ocean[j] < lowestValue) {
					lowestValue = Ocean[j];
					lowestIndex = j;
				}
			}
			Ocean[lowestIndex] += 1;
		}

	}
	else if (balanceCorrect > 25) {
		UE_LOG(LogTemp, Warning, TEXT("Sifting for OverBalance"));
		int32 remainderSift = balanceCorrect - 25;
		int32 highestValue;
		int32 highestIndex = 4;

		for (size_t i = 0; i < remainderSift; i++) {

			highestValue = -5;
			highestIndex = 4;
			for (size_t j = 0; j < 5; j++) {
				if (Ocean[j] > highestValue) {
					highestValue = Ocean[j];
					highestIndex = j;
				}
			}
			Ocean[highestIndex] -= 1;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Aft %d, %d, %d, %d, %d"), Ocean[0], Ocean[1], Ocean[2], Ocean[3], Ocean[4]);
	return Ocean;




	//Divide a, b, c by sum
	//Multiple a, b, c by given desired sum integer, and then round a, b, c to the nearest integer
	//See if sum(a, b, c) == given integer ? get result : try again

}

