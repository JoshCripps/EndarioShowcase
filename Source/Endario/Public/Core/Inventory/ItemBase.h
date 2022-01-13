// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/Texture2D.h"
#include "Engine/DataTable.h"
#include "Core/Enums/ItemDetails/EItemType.h"
#include "ItemBase.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FItemDataTable : public FTableRowBase
{
	GENERATED_BODY()

public:




	UPROPERTY(EditAnywhere, BlueprintReadonly)
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadonly)
	EItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadonly)
	UTexture2D* ItemIcon;

	UPROPERTY(EditAnywhere, BlueprintReadonly)
	int ItemStack;


	UPROPERTY(EditAnywhere, BlueprintReadonly)
	FString ItemTooltipName;

	UPROPERTY(EditAnywhere, BlueprintReadonly)
	FString ItemTooltipType;

	UPROPERTY(EditAnywhere, BlueprintReadonly)
	FString ItemTooltipText;
};


UCLASS(DefaultToInstanced, EditInlineNew, Blueprintable)
class ENDARIO_API UItemBase : public UObject
{
	GENERATED_BODY()

public:

	UItemBase();

protected:

	UPROPERTY(BlueprintReadWrite, Category = "Item Variables")
	int ItemID;

	//UPROPERTY(BlueprintReadWrite, Category = "Item Variables")
	//FString Name;

	//// Convert to Enum
	//UPROPERTY(BlueprintReadWrite, Category = "Item Variables")
	//FString Type;

	//// Convert to Enum
	//UPROPERTY(BlueprintReadWrite, Category = "Item Variables")
	//int StackLimit;

	//UPROPERTY(BlueprintReadWrite, Category = "Item Variables")
	//UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadonly)
	UItemBase* ItemObject;

	UPROPERTY(EditAnywhere, BlueprintReadonly)
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadonly)
	EItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadonly)
	UTexture2D* ItemIcon;

	UPROPERTY(EditAnywhere, BlueprintReadonly)
	int ItemStack;

	UPROPERTY(EditAnywhere, BlueprintReadonly)
	FString ItemTooltipName;

	UPROPERTY(EditAnywhere, BlueprintReadonly)
	FString ItemTooltipType;

	UPROPERTY(EditAnywhere, BlueprintReadonly)
	FString ItemTooltipText;
	


	// Methods

	// Inits
	UFUNCTION(Category = "Item Inits")
	void InitItem(FName ItemRowName);

public:



	//Getters
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Item Getters")
	int GetID();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Item Getters")
	UItemBase* GetObject();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Item Getters")
	FString GetName();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Item Getters")
	EItemType GetType();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Item Getters")
	UTexture2D* GetIcon();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Item Getters")
	int GetStack();


	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Item Getters")
	FString GetTooltipName();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Item Getters")
	FString GetTooltipType();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Item Getters")
	FString GetTooltipText();



	// Utility
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Item Utility")
	bool CheckItem(FString GivenItemName);

};
