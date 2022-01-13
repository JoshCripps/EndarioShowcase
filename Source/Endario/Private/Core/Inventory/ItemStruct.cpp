// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Inventory/ItemStruct.h"
#include "CoreMinimal.h"
#include "Core/Inventory/ItemBase.h"
//#include "Core/Inventory/ItemStruct.h"

// Default Constructor
FItemStruct::FItemStruct() {

	//UItemBase* Item;
	//int Quantity;

	//auto Ref = ConstructorHelpers::FObjectFinder<UItemBase>(TEXT("Class'/Core/Inventory/Items/Resources/
	// 
	// .WoodLogs'"));
	//Item = Ref.Object;
	Quantity = 23;
	Item = nullptr;

	//Quantity = 0;
}

FItemStruct::FItemStruct(int RequestedID, int RequestedQuantity = 1) {

	//get;
	//CreateDefaultSubobject<UVillagerComponent>(TEXT("LeadVillagerActionsComponent"));
	//Cast<ACameraPawn>(GetPawn()); // Get Camera Pawn
	//CameraMovementRef = CameraPawnRef->PawnMovementComponent; // Get Camera Pawn

	//CreateDefaultSubobject<UVillagerComponent>(TEXT("LeadVillagerActionsComponent"));
	//Item = CreateDefaultSubobject<UItemBase>(TEXT("Class'/Script/Endario.WoodLogs'"));
	//Item = NewObject<UItemBase*>(TEXT("WoodLogs"));

	// auto Ref = ConstructorHelpers::FObjectFinder<UItemBase>(TEXT("Class'/Script/Endario.WoodLogs'"));
	// auto Ref = ConstructorHelpers::FClassFinder<UItemBase>(TEXT("Class'/Script/Endario.WoodLogs'"));
	// 
	// static ConstructorHelpers::FObjectFinder<UItemBase>(TEXT("Class'/Script/Endario.WoodLogs'"));

	// static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("Class'/Script/Endario.WoodLogs'"));
	// DefaultPawnClass = PlayerPawnClassFinder.Class;
	// Item = Ref.Object;

	// Item= UItemBase::GetClass()->GetDefaultObject<UItemBase>();
	// Item= InstanceOfUItemBase->GetClass()->GetDefaultObject<UItemBase>();

	//or

	//Item = CreateDefaultSubobject<UItemBase>(TEXT("TEST"));

	//	UYourClass * ClassDefaultObject = InstanceOfYourClass->GetClass()->GetDefaultObject<UYourClass>()

	// TEMPORARY!
	//CameraPawnRef = Cast<ACameraPawn>(); // Get Camera Pawn

	//UE_LOG(LogTemp, Warning, TEXT("Okay Josh ARE YOU READY?"));

	//Item = nullptr;
	//Quantity = 0;
}

FItemStruct::FItemStruct(FString RequestedName, int RequestedQuantity = 1) {

	// Not Sure
	// Add for Dynamic -> Currently just output logs


	// Wood Log.

	auto Ref = ConstructorHelpers::FObjectFinder<UWoodLogs>(TEXT("Class'/Script/Endario.WoodLogs'"));

	Item = Ref.Object;

	//Item = nullptr;
	Quantity = RequestedQuantity;




}


FItemStruct::FItemStruct(UItemBase* RequestedItem, int RequestedQuantity = 1) {

	Item = RequestedItem;

	//Item = nullptr;
	Quantity = RequestedQuantity;
}

//
//FItemStruct* FItemStruct::SetItem(FString RequestedName, int RequestedQuantity = 1) {
//
//	//Item = ;
//
//	return this;
//}

//void FItemStruct::SetItem(UItemBase* GivenItem) {
//
//	Item = GivenItem;
//}
//
//ItemStruct::~ItemStruct()
//{
//}
