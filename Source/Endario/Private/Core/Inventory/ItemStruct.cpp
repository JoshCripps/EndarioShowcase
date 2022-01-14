// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Inventory/ItemStruct.h"
#include "CoreMinimal.h"
#include "Core/Inventory/ItemBase.h"

// Default Constructor
FItemStruct::FItemStruct() {

	Quantity = 23;
	Item = nullptr;
}

FItemStruct::FItemStruct(int RequestedID, int RequestedQuantity = 1) {

}

FItemStruct::FItemStruct(FString RequestedName, int RequestedQuantity = 1) {

	auto Ref = ConstructorHelpers::FObjectFinder<UWoodLogs>(TEXT("Class'/Script/Endario.WoodLogs'"));
	Item = Ref.Object;
	Quantity = RequestedQuantity;
}

FItemStruct::FItemStruct(UItemBase* RequestedItem, int RequestedQuantity = 1) {

	Item = RequestedItem;
	Quantity = RequestedQuantity;
}
