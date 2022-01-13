// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "..\Public\MainGameInstance.h"

UMainGameInstance::UMainGameInstance(const FObjectInitializer& ObjectInitializer) {


	//static ConstructorHelpers::FClassFinder<UUserWidget>UnitInfoWidget(TEXT("/Game/Widgets/UnitInfoHub"));
	//if (!ensure (UnitInfoWidget.Class != nullptr) && UnitInfoWidget.Succeeded) {
	//	UE_LOG(LogTemp, Warning, TEXT("No Widget as class is null"));
	//}

	//UnitInfoWidgetClass = UnitInfoWidget.Class;
	//static ConstuctorHelpers::FClassFinder<UUserWidget>UnitInfoHub(TEXT("WidgetBlueprint'/Game/Widgets/UnitInfoHub.UnitInfoHub'"))
}

void UMainGameInstance::Init() {


	//UE_LOG(LogTemp, Warning, TEXT("We have found class %s"), *UnitInfoWidgetClass->GetName());

}

void UMainGameInstance::ToggleWidget(bool bNewToggleWidget) {

	//UUserWidget* UnitInfo = CreateWidget<UUserWidget>(this, UnitInfoWidgetClass);

	//if (bNewToggleWidget) {

	//	UnitInfo = CreateWidget<UUserWidget>(this, UnitInfoWidgetClass);
	//	UnitInfo->AddToViewport();
	//}
	//else {

	//	if (UnitInfo != nullptr) {

	//		//UE_LOG(LogTemp, Warning, TEXT("LALALA") );
	//		UnitInfo->RemoveFromViewport();
	//	}
	//	//UUserWidget* UnitInfo = CreateWidget<UUserWidget>(this, UnitInfoWidgetClass);
	//	//UnitInfo->AddToViewport();
	//	//this->GetWid
	//	//UUserWidget* UnitInfo = GetWidget<UUserWidget>(this, UnitInfoWidgetClass);


	//}

	///* Get reference to player controller */
	//APlayerController* MainPlayerController = GetFirstLocalPlayerController();

	///* Set Up Input Parameters to the SetInputMode Function */
	//FInputModeUIOnly InputModeData;

	//InputModeData.SetWidgetToFocus(UnitInfo->TakeWidget());
	//InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	///* Set Input Mode */
	//MainPlayerController->SetInputMode(InputModeData);

	///* Show Cursor */
	//MainPlayerController->bShowMouseCursor = true;


	//UE_LOG(LogTemp, Warning, TEXT("Continue Calling") );

}

UUserWidget* UMainGameInstance::GetUnitInfoWidget() {

	//if (UnitInfo != nullptr) {

	//	return UnitInfo;
	//}
	//else {
	//	return nullptr;
	//}
		return nullptr;
}