// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Inventory/Items/Resources/WoodLogs.h"

// Constructor
UWoodLogs::UWoodLogs() {

	InitItem(FName(TEXT("WoodLogs")));
	//ItemID = 1;

	//ItemName = "WoodLogs";

	//ItemType = EItemType::Resource;

	//ItemStack = 100;

	//// Set the Item Texture
	//static ConstructorHelpers::FObjectFinder<UTexture2D> IconInfo(TEXT("Texture2D'/Game/Graphics/WoodLogs2D.WoodLogs2D'"));
	//if (IconInfo.Object != NULL) {
	//	ItemIcon = IconInfo.Object;
	//}
	//else {
	//	ItemIcon = nullptr;
	//}

}
