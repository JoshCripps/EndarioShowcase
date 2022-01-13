// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Inventory/InventoryComponent.h"
#include "Endario/Public/Core/Inventory/Items/Resources/StoneRocks.h"
#include "Endario/Public/Core/Inventory/Items/Refined/WoodPlanks.h"
#include "Endario/Public/Core/Inventory/Items/Refined/StoneBricks.h"
#include "Endario/Public/Core/Inventory/Items/RawFood/RawBerries.h"
#include "Endario/Public/Core/Inventory/Items/CookedFood/CookedBerries.h"

//#include "Core/Inventory/ItemStruct.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Default Slot Limit
	SlotLimit = 3; // Default Assumes villagers..
	StackLimit = 10; // Default Assumes villagers..

	// ...
}

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent(int RequestedSlotLimit, int RequestedStackLimit)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Default Slot Limit
	SlotLimit = RequestedSlotLimit;
	StackLimit = RequestedStackLimit;
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


// INITS
// Initialise Inventory
void UInventoryComponent::InitInventory(int RequestedSlotLimit = 3, int RequestedStackLimit = 10) {

	SlotLimit = RequestedSlotLimit;
	StackLimit = RequestedStackLimit;

	FItemStruct Empty(nullptr, 0);

	InventorySlots.Init(Empty, SlotLimit);
	//InventorySlots = [nullptr, nullptr, nullptr};
}

// Fill Inventory
bool UInventoryComponent::FillInventory(UItemBase* RequestedItem, int RequestedQuantity) {


	FItemStruct NewSlot(RequestedItem, RequestedQuantity);

	// See if there is available slot
	for (int i = 0; i < SlotLimit; i++) {
		if (InventorySlots[i].Item == nullptr) {

			// If Slot - fill and return true!
			InventorySlots[i] = NewSlot;
			return true;
		}
	}

	// Reaching here means no space to fill
	return false;

}

// SETTERS
// Set Slot Limit
void UInventoryComponent::SetSlotLimit(int RequestedLimit) {
	SlotLimit = RequestedLimit;
}

void UInventoryComponent::SetStackLimit(int RequestedLimit) {
	StackLimit = RequestedLimit;
}



// GETTERS
FItemStruct UInventoryComponent::GetSlotData(int RequestedSlot) {

	if (this != nullptr) {
		

		if (RequestedSlot < InventorySlots.Num()) {

			return this->InventorySlots[RequestedSlot];
		}
	}

	// Else 
	FItemStruct FTemp;
	return FTemp;

}



// UTILITY

bool UInventoryComponent::CollectItem(FString TransferableItemName, int TransferableQuantity, UInventoryComponent* GivingInventory, float& CurrentProgress) {


	// TODO: Account for TransferableQuantitys of chunks at a time
	// TODO: Review Repeats of For Loops we could return significant index for cheaper right?
	
	//ReceivingInventory->StockOfItem();

	//UE_LOG(LogTemp, Warning, TEXT("This is AntiClimactic"));

	 
	// Check If Receiver has space to receive it
	int ReceiverSpace = SpaceForItem(TransferableItemName);
	if (ReceiverSpace <= 0) return false;

	// Check If Giver has enough item(s)
	int GiverStock = GivingInventory->StockOfItem(TransferableItemName);
	if (GiverStock <= 0) return false;

	//UE_LOG(LogTemp, Warning, TEXT("Space %d, Stock %d"), ReceiverSpace, GiverStock);

	// Take From Giver.
	GivingInventory->TakeItemFromInventory(TransferableItemName, TransferableQuantity);

	// Give To Receiver
	GiveItemToInventory(TransferableItemName, TransferableQuantity);

	CurrentProgress = float(StackLimit - ReceiverSpace+TransferableQuantity) / float(StackLimit);

	return true;
}


// Drop off at storage buildings
bool UInventoryComponent::DropoffItem(FString TransferableItemName, UInventoryComponent* ReceivingInventory) {

	// See how much Giver has to give 
	int GiverStock = StockOfItem(TransferableItemName);
	//UE_LOG(LogTemp, Warning, TEXT("Stock: %d"), GiverStock);
	if (GiverStock <= 0) return false;

	// Check If Receiver has space to receive it
	int ReceiverSpace = ReceivingInventory->SpaceForItem(TransferableItemName);
	//UE_LOG(LogTemp, Warning, TEXT("Space: %d"), ReceiverSpace);
	if (ReceiverSpace <= GiverStock) return false;

	//UE_LOG(LogTemp, Warning, TEXT("Item: %s"), *FString(TransferableItemName));
	TakeItemFromInventory(TransferableItemName, GiverStock);

	// Give To Receiver
	ReceivingInventory->GiveItemToInventory(TransferableItemName, GiverStock);


	return true;

}

bool UInventoryComponent::ConvertItem(FString TransferableItemInputName, FString TransferableItemOutputName, float& CurrentProgress) {

	// See how much Input Item has to give 
	int GiverStock = StockOfItem(TransferableItemInputName);
	//UE_LOG(LogTemp, Warning, TEXT("Stock: %d"), GiverStock);
	if (GiverStock <= 0) return false;

	// Check If Space there is for Output Item
	int ReceiverSpace = SpaceForItem(TransferableItemOutputName);
	//UE_LOG(LogTemp, Warning, TEXT("Space: %d"), ReceiverSpace);
	if (ReceiverSpace <= 0) return false;

	TakeItemFromInventory(TransferableItemInputName, 1);
	GiveItemToInventory(TransferableItemOutputName, 1);
	
	CurrentProgress = float(StackLimit - ReceiverSpace + 1) / float(StackLimit);

	return true;
}

bool UInventoryComponent::AbsorbItem(FString TransferableItemName, int TransferableQuantity, UInventoryComponent* GivingInventory) {

	// See how much Input Item has to give 
	int GiverStock = GivingInventory->StockOfItem(TransferableItemName);
	// UE_LOG(LogTemp, Warning, TEXT("Stock: %d"), GiverStock);
	if (GiverStock <= 0) return false;

	GivingInventory->TakeItemFromInventory(TransferableItemName, 1);
	
	return true;
}

bool UInventoryComponent::ModifyItemQuantitiy(FString TransferableItemName, int AdditionalQuantity) {

	GiveItemToInventory(TransferableItemName, AdditionalQuantity);
	return true;
}



// Supporting
int UInventoryComponent::SpaceForItem(FString TransferableItemName) {

	// Check if currently holding item
	for (size_t i = 0; i < this->SlotLimit; i++) {

		// Check to see if currently holding item.
		if (this->InventorySlots[i].Item->CheckItem(TransferableItemName)) {
			//this->InventorySlots[i].Item->
			//this->InventorySlots[i].Ite;

			// Return space left to fill this slot
			return this->StackLimit - this->InventorySlots[i].Quantity;
		}
	}

	// If not currently holding item and there is an empty slot then space is the stack limit
	for (size_t i = 0; i < this->SlotLimit; i++) {
		if (this->InventorySlots[i].Quantity == 0) {
			return this->StackLimit;
		}
	}

	// Else no space
	return 0;


}

int UInventoryComponent::StockOfItem(FString TransferableItemName) {

	// Check if currently holding item
	for (size_t i = 0; i < this->SlotLimit; i++) {

		// Check to see if currently holding item.
		if (this->InventorySlots[i].Item->CheckItem(TransferableItemName)) {

			// Return space left to fill this slot
			return this->InventorySlots[i].Quantity;
		}
	}

	return 0;
}

void UInventoryComponent::TakeItemFromInventory(FString TransferableItemName, int TransferableQuantity) {

	for (size_t i = 0; i < this->SlotLimit; i++) {

		if (this->InventorySlots[i].Item->CheckItem(TransferableItemName)) {

			// Remove Quantity of Items and Set to Nullptr if all items gone
			this->InventorySlots[i].Quantity -= TransferableQuantity;

			if (this->InventorySlots[i].Quantity == 0) {
				this->InventorySlots[i].Item = nullptr;
				return;
			}
		}
	}
}

void UInventoryComponent::GiveItemToInventory(FString TransferableItemName, int TransferableQuantity) {
	
	// Add to Item if Found
	for (size_t i = 0; i < this->SlotLimit; i++) {

		if (this->InventorySlots[i].Item->CheckItem(TransferableItemName)) {

			// Remove Quantity of Items and Set to Nullptr if all items gone
			this->InventorySlots[i].Quantity += TransferableQuantity;
			return;
		}
	}

	// Otherwise Create new Item at first available Slot
	for (size_t i = 0; i < this->SlotLimit; i++) {

		if (this->InventorySlots[i].Quantity == 0) {

			// Construct Wood Logs make dynamic after!!
			
			UItemBase* TransferableItem;
			// Make Dynamic with DataTable!!
			if (TransferableItemName == "WoodLogs") {
				TransferableItem = NewObject<UWoodLogs>(this);
			}
			else if (TransferableItemName == "StoneRocks") {
				TransferableItem = NewObject<UStoneRocks>(this);
			}
			else if (TransferableItemName == "WoodPlanks") {
				TransferableItem = NewObject<UWoodPlanks>(this);
			}
			else if (TransferableItemName == "StoneBricks") {
				TransferableItem = NewObject<UStoneBricks>(this);
			}
			else if (TransferableItemName == "RawBerries") {
				TransferableItem = NewObject<URawBerries>(this);
			}
			else if (TransferableItemName == "CookedBerries") {
				TransferableItem = NewObject<UCookedBerries>(this);
			}
			else {
				TransferableItem = NewObject<UWoodLogs>(this);
			}

			// Construct New Instance of Object
			this->InventorySlots[i].Item = TransferableItem;
			this->InventorySlots[i].Quantity = TransferableQuantity;

			//UE_LOG(LogTemp, Warning, TEXT("Created New Instance of WoodLogs!!!!!!!!"));
			return;
		}
	}

}
