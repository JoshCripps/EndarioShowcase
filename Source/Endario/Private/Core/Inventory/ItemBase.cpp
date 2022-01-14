// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Inventory/ItemBase.h"

UItemBase::UItemBase() {

	ItemName = "DefaultName";
}


// Inits
void UItemBase::InitItem(FName ItemRowName) {

	UDataTable* CurrentTable;
	TArray<FName> RowNames;
	static ConstructorHelpers::FObjectFinder<UDataTable> FoundTable(TEXT("DataTable'/Game/Enums/ItemDataFilled.ItemDataFilled'"));
	if (FoundTable.Succeeded()) {
		CurrentTable = FoundTable.Object;

		RowNames = CurrentTable->GetRowNames();

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
