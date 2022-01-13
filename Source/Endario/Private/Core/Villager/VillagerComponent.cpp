// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Villager/VillagerComponent.h"
#include "Core/Villager/VillagerLead.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
//#include "Blueprint/UserWidget.h" // Widget
//#include "UObject/ConstructorHelpers.h" // Widget

// Sets default values for this component's properties
UVillagerComponent::UVillagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...




	//static ConstructorHelpers::FClassFinder<UUserWidget>UnitInfoWidget(TEXT("/Game/Widgets/UnitInfoHub"));
	//if (!ensure(UnitInfoWidget.Class != nullptr)) {
	//	UE_LOG(LogTemp, Warning, TEXT("No Widget as class is null"));
	//}

	//UnitInfoWidgetClass = UnitInfoWidget.Class;

}


// Called when the game starts
void UVillagerComponent::BeginPlay()
{
	Super::BeginPlay();

	//UE_LOG(LogTemp, Warning, TEXT("Im called at the start: Component"));

	//UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite)
	VillagerOwner = Cast<AVillagerLead>(GetOwner());
	// ...

	// This should be controlled by AI Controller...
	//MoveVillagerTo(30.0f, 30.0f);

	//CallDisplayUnitHUD(VillagerOwner, false);
	
}


// Called every frame
void UVillagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UVillagerComponent::MoveVillagerTo(float PositionX, float PositionY) {

	UE_LOG(LogTemp, Warning, TEXT("Calling Villager Move To!"));

}


void UVillagerComponent::CallDisplayUnitHUD(AVillagerLead* HitActor, bool Bypass) {

	//UE_LOG(LogTemp, Warning, TEXT("Calling Display Villager HUD 2"));







}



//
//// Widget Stuff
//void UVillagerComponent::InitWidgetUnit() {
//
//	UE_LOG(LogTemp, Warning, TEXT("We have found class %s"), *UnitInfoWidgetClass->GetName());
//
//}
//
//void UVillagerComponent::ShowWidgetUnit() {
//	UUserWidget* UnitInfo = CreateWidget<UUserWidget>(this, UnitInfoWidgetClass);
//	UnitInfo->AddToViewport();
//
//	/* Get reference to player controller */
//	//APlayerController* MainPlayerController = GetFirstLocalPlayerController();
//	APlayerController* MainPlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
//
//	/* Set Up Input Parameters to the SetInputMode Function */
//	FInputModeUIOnly InputModeData;
//	InputModeData.SetWidgetToFocus(UnitInfo->TakeWidget());
//	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
//
//	/* Set Input Mode */
//	MainPlayerController->SetInputMode(InputModeData);
//
//	/* Show Cursor */
//	MainPlayerController->bShowMouseCursor = true;
//
//}

