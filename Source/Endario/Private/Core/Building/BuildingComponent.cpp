// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Building/BuildingComponent.h"

// Sets default values for this component's properties
UBuildingComponent::UBuildingComponent() {
	PrimaryComponentTick.bCanEverTick = true;

	EBuildingType = EEndlingBuildingType::Stockpile;
}

// Called when the game starts
void UBuildingComponent::BeginPlay() {

	Super::BeginPlay();
}

// Called every frame
void UBuildingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
