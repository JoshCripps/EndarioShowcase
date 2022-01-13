// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Interest/ResourceGeneral.h"

// Sets default values
AResourceGeneral::AResourceGeneral()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	BuildingModel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Resource Model"));
	BuildingModel->SetupAttachment(Root);
	BuildingModel->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));


	StimuliSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("StimuliSource"));
	//StimuliSource->RegisterForSense( TSubclassOf<UAISense_Sight>() );
	//StimuliSource->RegisterWithPerceptionSystem();
	//StimuliSource->Registersense; 

	// Components
	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
	Selection = CreateDefaultSubobject<USelectionComponent>(TEXT("Selection"));
	//InitSelection(this);

	Inventory->InitInventory(4, 10);
	Selection->InitSelection(EEndlingType::Resource, EEndlingSelectionSize::MediumResource);
}

// Called when the game starts or when spawned
void AResourceGeneral::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AResourceGeneral::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AResourceGeneral::SetResourceType(EEndlingResourceType ERequestedType) {

	EResourceType = ERequestedType;
}


void AResourceGeneral::SetResourceVillager(AVillagerUnit* VillagerToEngage) {

	EngagedVillager = VillagerToEngage;
}