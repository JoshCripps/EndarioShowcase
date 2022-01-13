// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Inventory/ItemBase.h"

UItemBase::UItemBase() {

	ItemName = "DefaultName";
}


// Inits

void UItemBase::InitItem(FName ItemRowName) {


	//UE_LOG(LogTemp, Warning, TEXT("Going to Test The DataTable Method!"));

	UDataTable* CurrentTable;
	TArray<FName> RowNames;
	static ConstructorHelpers::FObjectFinder<UDataTable> FoundTable(TEXT("DataTable'/Game/Enums/ItemDataFilled.ItemDataFilled'"));
	if (FoundTable.Succeeded()) {
		CurrentTable = FoundTable.Object;

		RowNames = CurrentTable->GetRowNames();
		//UE_LOG(LogTemp, Warning, TEXT("DataTable Found Table!"));
		//for (size_t i = 0; i < RowNames.Num(); i++) {

		//	if (RowNames[i] == ItemRowName) {
		//		// Success!

		//		break;
		//	}
		//	UE_LOG(LogTemp, Warning, TEXT("Getting Row Names: %s"), *RowNames[i].ToString());
		//}

		//static FString ContextString(TEXT("Temporary Lala"));
		//FItemDataTable* OutRow = CurrentTable->FindRow<FItemDataTable>(RowNames[0], "");
		FItemDataTable* FoundRow = CurrentTable->FindRow<FItemDataTable>(ItemRowName, "");

		if (FoundRow != nullptr) {

			ItemName =   FoundRow->ItemName;
			ItemType =   FoundRow->ItemType;
			ItemStack =  FoundRow->ItemStack;
			ItemIcon =   FoundRow->ItemIcon;

			ItemTooltipName = FoundRow->ItemTooltipName;
			ItemTooltipType = FoundRow->ItemTooltipType;
			ItemTooltipText = FoundRow->ItemTooltipText;
		}

		//UE_LOG(LogTemp, Warning, TEXT("Found Row Name: %s"), *OutRow->ItemName);
	}
}


// Getters
int UItemBase::GetID() {

	return ItemID;
}

UItemBase* UItemBase::GetObject() {

	return ItemObject;
}

FString UItemBase::GetName() {

	return ItemName;
}

EItemType UItemBase::GetType() {

	return ItemType;
}

UTexture2D* UItemBase::GetIcon() {

	return ItemIcon;
}

int UItemBase::GetStack() {

	return ItemStack;
}

FString UItemBase::GetTooltipName() {

	return ItemTooltipName;
}

FString UItemBase::GetTooltipType() {

	return ItemTooltipType;
}

FString UItemBase::GetTooltipText() {

	return ItemTooltipText;
}

//FString UItemBase::GetName() {
//
//	return Name;
//}
//
//UTexture2D* UItemBase::GetIcon() {
//
//	return Icon;
//}

bool UItemBase::CheckItem(FString GivenItemName) {

	if (this == nullptr) {
		return false;
	}

	if (ItemName == GivenItemName) {
		return true;
	}
	else {
		return false;
	}
}

