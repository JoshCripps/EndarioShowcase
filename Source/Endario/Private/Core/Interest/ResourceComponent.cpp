// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Interest/ResourceComponent.h"

// Sets default values for this component's properties
UResourceComponent::UResourceComponent() {
	PrimaryComponentTick.bCanEverTick = true;

	ResourceAmount = 32;
	EngagedVillager = nullptr;
}

// Called when the game starts
void UResourceComponent::BeginPlay() {
	Super::BeginPlay();

}

// Called every frame
void UResourceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UResourceComponent::SetResourceVillager(AVillagerUnit* VillagerToEngage) {

	EngagedVillager = VillagerToEngage;
}
