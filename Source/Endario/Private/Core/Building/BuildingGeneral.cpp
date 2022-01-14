// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Building/BuildingGeneral.h"
#include "Core/Inventory/InventoryComponent.h"
#include "Core/SelectionUI/SelectionComponent.h"

// Sets default values
ABuildingGeneral::ABuildingGeneral() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	BuildingModel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Building Model"));
	BuildingModel->SetupAttachment(Root);
	BuildingModel->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	// Components
	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
	Selection = CreateDefaultSubobject<USelectionComponent>(TEXT("Selection"));

	Inventory->InitInventory(4, 10);
	Selection->InitSelection(EEndlingType::Building, EEndlingSelectionSize::SmallBuilding);

	EBuildingInteraction = EEndlingBuildingInteractionType::Outer;
}

// Called when the game starts or when spawned
void ABuildingGeneral::BeginPlay() {

	Super::BeginPlay();
}

// Called every frame
void ABuildingGeneral::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);
}

// Setters
void ABuildingGeneral::SetBuildingType(EEndlingBuildingType ERequestedType) {

	EBuildingType = ERequestedType;

	// For (Default) Interactions
	if (ERequestedType == EEndlingBuildingType::Stockpile ||
		  ERequestedType == EEndlingBuildingType::Granary) {

		EBuildingInteraction = EEndlingBuildingInteractionType::Outer;
	}
	else if (ERequestedType == EEndlingBuildingType::Lumbermill ||
		       ERequestedType == EEndlingBuildingType::MasonHouse ||
			     ERequestedType == EEndlingBuildingType::BuildersYard ||
			     ERequestedType == EEndlingBuildingType::Kitchen ||
			     ERequestedType == EEndlingBuildingType::House) {

		EBuildingInteraction = EEndlingBuildingInteractionType::Fixed;
	}
	else if (ERequestedType == EEndlingBuildingType::Hearth) {

		EBuildingInteraction = EEndlingBuildingInteractionType::Fixed;
	}

	// For (Default) Groupings
	if (ERequestedType == EEndlingBuildingType::Hearth ||
		ERequestedType == EEndlingBuildingType::House) {

		EBuildingGroup = EEndlingBuildingGroup::Routine;
	}
	else if (ERequestedType == EEndlingBuildingType::Stockpile ||
		ERequestedType == EEndlingBuildingType::Granary ||
		ERequestedType == EEndlingBuildingType::BuildersYard) {

		EBuildingGroup = EEndlingBuildingGroup::Storage;
	}
	else if (ERequestedType == EEndlingBuildingType::Lumbermill ||
		ERequestedType == EEndlingBuildingType::MasonHouse ||
		ERequestedType == EEndlingBuildingType::Kitchen) {

		EBuildingGroup = EEndlingBuildingGroup::Refiner;
	}
}

void ABuildingGeneral::SetBuildingInteraction(EEndlingBuildingInteractionType ERequestedInteraction) {

	EBuildingInteraction = ERequestedInteraction;
}
