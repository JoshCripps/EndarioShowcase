// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Villager/Professions/ProfessionComponent.h"
#include "Core/Inventory/ItemBase.h"
#include "Core/Inventory/ItemStruct.h"

// Sets default values for this component's properties
UProfessionComponent::UProfessionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	EVillagerClass = EEndlingClass::Lumberjack;

	EVillagerClassType = EEndlingClassType::Harvester;

	EVillagerInterest = EEndlingResourceType::Tree;

	EVillagerBuilding = EEndlingBuildingType::Stockpile;

	EVillagerStorage = EEndlingBuildingType::Stockpile;
}


// Called when the game starts
void UProfessionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UProfessionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}



// Setters
//void UProfessionComponent::SetVillagerClassInfo(EEndlingClass ERequestedClass, EEndlingResourceType ERequestedResource, EEndlingBuildingType ERequestedBuilding) {
//
//	EVillagerClass = ERequestedClass;
//	EVillagerInterest = ERequestedResource;
//	EVillagerBuilding = ERequestedBuilding;
//}

// Setters
void UProfessionComponent::SetVillagerClassInfo(EEndlingClass ERequestedClass) {

	EVillagerClass = ERequestedClass;

	// Get Class Types
	if (ERequestedClass == EEndlingClass::Lumberjack ||
		ERequestedClass == EEndlingClass::Miner ||
		ERequestedClass == EEndlingClass::Gatherer) {

		EVillagerClassType = EEndlingClassType::Harvester;

	}
	else if (ERequestedClass == EEndlingClass::Woodworker ||
			 ERequestedClass == EEndlingClass::Stonemason ||
			 ERequestedClass == EEndlingClass::Cook) {

		EVillagerClassType = EEndlingClassType::Refiner;
	}
	else {

		EVillagerClassType = EEndlingClassType::Harvester;
	}


	// For Harvesters
	if (EVillagerClassType == EEndlingClassType::Harvester) {

		if (EVillagerClass == EEndlingClass::Lumberjack) {

			EVillagerInterest = EEndlingResourceType::Tree;
			EVillagerStorage = EEndlingBuildingType::Stockpile;
			NameItemOutput = FName(TEXT("WoodLogs"));
		}
		else if (EVillagerClass == EEndlingClass::Miner) {

			EVillagerInterest = EEndlingResourceType::Cave;
			EVillagerStorage = EEndlingBuildingType::Stockpile;
			NameItemOutput = FName(TEXT("StoneRocks"));
		}
		else if (EVillagerClass == EEndlingClass::Gatherer) {

			EVillagerInterest = EEndlingResourceType::Bush;
			EVillagerStorage = EEndlingBuildingType::Granary;
			NameItemOutput = FName(TEXT("RawBerries"));
		}
	}



	// For Refiners
	if (EVillagerClassType == EEndlingClassType::Refiner) {

		if (EVillagerClass == EEndlingClass::Woodworker) {

			EVillagerSource = EEndlingBuildingType::Stockpile;
			EVillagerBuilding = EEndlingBuildingType::Lumbermill;
			EVillagerStorage = EEndlingBuildingType::BuildersYard;

			NameItemInput = FName(TEXT("WoodLogs"));
			NameItemOutput = FName(TEXT("WoodPlanks"));
		}
		else if (EVillagerClass == EEndlingClass::Stonemason) {

			EVillagerSource = EEndlingBuildingType::Stockpile;
			EVillagerBuilding = EEndlingBuildingType::MasonHouse;
			EVillagerStorage = EEndlingBuildingType::BuildersYard;

			NameItemInput = FName(TEXT("StoneRocks"));
			NameItemOutput = FName(TEXT("StoneBricks"));
		}
		else if (EVillagerClass == EEndlingClass::Cook) {

			EVillagerSource = EEndlingBuildingType::Granary;
			EVillagerBuilding = EEndlingBuildingType::Kitchen;
			EVillagerStorage = EEndlingBuildingType::Hearth;

			NameItemInput = FName(TEXT("RawBerries"));
			NameItemOutput = FName(TEXT("CookedBerries"));
		}
	}




}
