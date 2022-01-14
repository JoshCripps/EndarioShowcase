// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Core/Inventory/ItemStruct.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ENDARIO_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInventoryComponent();
	UInventoryComponent(int RequestedSlotLimit, int RequestedStackLimit);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(Category = "Inventory Slots", VisibleAnywhere, BlueprintReadOnly)
	TArray<FItemStruct> InventorySlots;

	UPROPERTY(Category = "Inventory Details", VisibleAnywhere, BlueprintReadOnly)
	int SlotLimit;

	UPROPERTY(Category = "Inventory Details", VisibleAnywhere, BlueprintReadOnly)
	int StackLimit;

public:

	// Inits
	UFUNCTION(BlueprintCallable, Category = "Inventory Setup")
	void InitInventory(int RequestedSlotLimit, int RequestedStackLimit);

	UFUNCTION(BlueprintCallable , Category = "Inventory Setup")
	bool FillInventory(UItemBase* RequestedItem, int RequestedQuantity);

	// Getters
	UFUNCTION(BlueprintCallable, Category = "Inventory Setup")
	FItemStruct GetSlotData(int RequestedSlot);

	// Setters
	UFUNCTION(BlueprintCallable, Category = "Inventory Setup")
	void SetSlotLimit(int RequestedLimit);

	UFUNCTION(BlueprintCallable, Category = "Inventory Setup")
	void SetStackLimit(int RequestedLimit);

	// Utility
	UFUNCTION(BlueprintCallable, Category = "Inventory Utility")
	bool CollectItem(FString TransferableItemName, int TransferableQuantity, UInventoryComponent* GivingInventory, float& CurrentProgress);

	UFUNCTION(BlueprintCallable, Category = "Inventory Utility")
	bool DropoffItem(FString TransferableItemName, UInventoryComponent* ReceivingInventory);

	UFUNCTION(BlueprintCallable, Category = "Inventory Utility")
	bool ConvertItem(FString TransferableItemInputName, FString TransferableItemOutputName, float& CurrentProgress);

	UFUNCTION(BlueprintCallable, Category = "Inventory Utility")
	bool AbsorbItem(FString TransferableItemName, int TransferableQuantity, UInventoryComponent* GivingInventory);

	UFUNCTION(BlueprintCallable, Category = "Inventory Utility")
	bool ModifyItemQuantitiy(FString TransferableItemName, int AdditionalQuantity);

	// Supporting
	UFUNCTION(BlueprintCallable, Category = "Inventory Supporting")
	int SpaceForItem(FString TransferableItemName);

	UFUNCTION(BlueprintCallable, Category = "Inventory Supporting")
	int StockOfItem(FString TransferableItemName);

	UFUNCTION(Category = "Inventory Supporting")
	void TakeItemFromInventory(FString TransferableItemName, int TransferableQuantity);

	UFUNCTION(Category = "Inventory Supporting")
	void GiveItemToInventory(FString TransferableItemName, int TransferableQuantity);
};
