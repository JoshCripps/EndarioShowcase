// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Villager/VillagerComponent.h"
#include "Core/Villager/VillagerLead.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UVillagerComponent::UVillagerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UVillagerComponent::BeginPlay()
{
	Super::BeginPlay();

	VillagerOwner = Cast<AVillagerLead>(GetOwner());
}


// Called every frame
void UVillagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void UVillagerComponent::MoveVillagerTo(float PositionX, float PositionY) {

	UE_LOG(LogTemp, Warning, TEXT("Calling Villager Move To!"));

}


void UVillagerComponent::CallDisplayUnitHUD(AVillagerLead* HitActor, bool Bypass) {

}
