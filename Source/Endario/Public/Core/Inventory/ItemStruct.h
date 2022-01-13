// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Inventory/ItemBase.h"
#include "Core/Inventory/Items/Resources/WoodLogs.h"
#include "Core/Player/CameraPawn.h"
#include "UObject/NoExportTypes.h"
#include "ItemStruct.generated.h"

/**
 * 
 */
//class ENDARIO_API ItemStruct
//{
//public:
//	ItemStruct();
//	~ItemStruct();
//};

USTRUCT(BlueprintType)
struct FItemStruct {

	GENERATED_USTRUCT_BODY();


public:

	FItemStruct();
	FItemStruct(int RequestedID, int RequestedQuantity);
	FItemStruct(FString RequestedName, int RequestedQuantity);
	FItemStruct(UItemBase* RequestedItem, int RequestedQuantity);

//protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	UItemBase* Item;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	int Quantity;


public:

	//// Getters


	//// Setters
	//UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Camera Location")
	//FItemStruct* SetItem(FString RequestedName, int RequestedQuantity);
};
