// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/SelectionUI/SelectionComponent.h"
#include "Core/Interest/ResourceGeneral.h"
#include "Core/Building/BuildingGeneral.h"
#include "GameFramework/Actor.h"

USelectionComponent::USelectionComponent () {

	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;

	bIsSelected = false;
	EOwnerType = EEndlingType::Unit;
	EOwnerSize = EEndlingSelectionSize::SmallBuilding;
	OwningActor = nullptr;

	// Set Static Mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Game/Models/Decals/Selection/SelectionPlaneSmallBuilding.SelectionPlaneSmallBuilding'"));
	UStaticMesh* Asset = MeshAsset.Object;

	this->SetStaticMesh(Asset);

	// For Materials
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAssetCharacter(TEXT("UMaterial'/Game/Models/Decals/Selection/DecalCharacter_Mat.DecalCharacter_Mat'"));
	MaterialRefCharacter = MaterialAssetCharacter.Object;

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAssetSmallBuilding(TEXT("UMaterial'/Game/Models/Decals/Selection/DecalSmallBuilding_Mat.DecalSmallBuilding_Mat'"));
	MaterialRefSmallBuilding = MaterialAssetSmallBuilding.Object;

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAssetMediumBuilding(TEXT("UMaterial'/Game/Models/Decals/Selection/DecalMediumBuilding_Mat.DecalMediumBuilding_Mat'"));
	MaterialRefMediumBuilding = MaterialAssetMediumBuilding.Object;

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAssetLargeBuilding(TEXT("UMaterial'/Game/Models/Decals/Selection/DecalLargeBuilding_Mat.DecalLargeBuilding_Mat'"));
	MaterialRefLargeBuilding = MaterialAssetLargeBuilding.Object;

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAssetSmallResource(TEXT("UMaterial'/Game/Models/Decals/Selection/DecalSmallResource_Mat.DecalSmallResource_Mat'"));
	MaterialRefSmallResource = MaterialAssetSmallResource.Object;

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAssetMediumResource(TEXT("UMaterial'/Game/Models/Decals/Selection/DecalMediumResource_Mat.DecalMediumResource_Mat'"));
	MaterialRefMediumResource = MaterialAssetMediumResource.Object;
}

void USelectionComponent::InitSelection(EEndlingType ERequestedEndlingType, EEndlingSelectionSize ERequestedSelectionSize) {

	// Set Type of Endling
	EOwnerType = ERequestedEndlingType;
	EOwnerSize = ERequestedSelectionSize;

	this->SetVisibility(true);

	//  Get Height of Actor
	OwningActor = Cast<AActor>(GetOwner());
	USelectionComponent* CurrentComponent = Cast<USelectionComponent>(this);

	if (OwningActor != nullptr) {

		FVector ActorOrigin;
		FVector ActorExtent;
		OwningActor->GetActorBounds(true, ActorOrigin, ActorExtent, true);
		if (CurrentComponent->IsRegistered()) {

		}
		else {
			this->SetupAttachment(OwningActor->GetRootComponent());
		}

		this->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

		if (EOwnerSize == EEndlingSelectionSize::Character) {

			this->SetMaterial(0, MaterialRefCharacter);
			this->SetRelativeScale3D(FVector(2.0f, 2.0f, 2.0f));
		}
		else if (EOwnerSize == EEndlingSelectionSize::SmallBuilding) {

			this->SetMaterial(0, MaterialRefSmallBuilding);
			this->SetRelativeScale3D(FVector(5.0f, 5.0f, 5.0f));
		}
		else if (EOwnerSize == EEndlingSelectionSize::MediumBuilding) {

			this->SetMaterial(0, MaterialRefMediumBuilding);
			this->SetRelativeScale3D(FVector(7.5f, 7.5f, 7.5f));
		}
		else if (EOwnerSize == EEndlingSelectionSize::LargeBuilding) {

			this->SetMaterial(0, MaterialRefLargeBuilding);
			this->SetRelativeScale3D(FVector(10.0f, 10.0f, 10.0f));
		}
		else if (EOwnerSize == EEndlingSelectionSize::SmallResource) {

			this->SetMaterial(0, MaterialRefSmallResource);
			this->SetRelativeScale3D(FVector(5.0f, 5.0f, 5.0f));
		}
		else if (EOwnerSize == EEndlingSelectionSize::MediumResource) {

			this->SetMaterial(0, MaterialRefMediumResource);
			this->SetRelativeScale3D(FVector(8.33f, 8.33f, 8.33f));
		}

		CurrentComponent->SetVisibility(false);
	}
}

// Getters
bool USelectionComponent::GetSelection() {

	return bIsSelected;
}

EEndlingType USelectionComponent::GetEndlingType() {

	if (this != nullptr) {
		return EOwnerType;
	}
	else {
		return EEndlingType::None;
	}
}

FEndlingUnitDetails USelectionComponent::GetEndlingUnitInfomation() {

	if (OwningActor == nullptr) OwningActor = Cast<AActor>(GetOwner());

	AVillagerUnit* CurrentUnit = Cast<AVillagerUnit>(OwningActor);

	if (CurrentUnit != nullptr) {

		FEndlingUnitDetails CurrentDetails;

		CurrentDetails.UnitFirstName = CurrentUnit->GetFirstName();
		CurrentDetails.UnitLastName = CurrentUnit->GetLastName();
		CurrentDetails.UnitGender = CurrentUnit->GetGender();
		CurrentDetails.UnitClass = CurrentUnit->GetClass();
		CurrentDetails.UnitOcean = CurrentUnit->GetOcean();

		if (CurrentUnit->GetClass() == EEndlingClass::Lumberjack ||
			CurrentUnit->GetClass() == EEndlingClass::Miner ||
			CurrentUnit->GetClass() == EEndlingClass::Gatherer) {

			UE_LOG(LogTemp, Warning, TEXT("Class is a Gatherer"));
		}
		else if (CurrentUnit->GetClass() == EEndlingClass::Woodworker ||
			CurrentUnit->GetClass() == EEndlingClass::Stonemason ||
			CurrentUnit->GetClass() == EEndlingClass::Cook) {

			UE_LOG(LogTemp, Warning, TEXT("Class is a Harvester"));
		}
		else {

			UE_LOG(LogTemp, Warning, TEXT("Class is a Unassigned??"));
		}

		return CurrentDetails;
	}
	else {
		FEndlingUnitDetails Temporary;
		return Temporary;
	}
}

FEndlingResourceDetails USelectionComponent::GetEndlingResourceInfomation() {

	AResourceGeneral* CurrentResource = Cast<AResourceGeneral>(OwningActor);
	EEndlingResourceType EResourceType = CurrentResource->GetResourceType();

	FEndlingResourceDetails TempDeets;

	if (EResourceType == EEndlingResourceType::Tree) {
		TempDeets.UnitResourceName = "Tree";
	}
	else if (EResourceType == EEndlingResourceType::Cave) {
		TempDeets.UnitResourceName = "Cave";

	}
	else if (EResourceType == EEndlingResourceType::Bush) {
		TempDeets.UnitResourceName = "Bush";
	}
	else {
		TempDeets.UnitResourceName = "Tree";
	}

	return TempDeets;
}

FEndlingBuildingDetails USelectionComponent::GetEndlingBuildingInfomation() {

	ABuildingGeneral* CurrentBuilding = Cast<ABuildingGeneral>(OwningActor);

	FEndlingBuildingDetails TempDeets;
	TempDeets.BuildingType = CurrentBuilding->GetBuildingType();
	TempDeets.BuildingGroup = CurrentBuilding->GetBuildingGroup();;

	return TempDeets;
}

// Utility

void USelectionComponent::ToggleSelection(bool bNewSelected) {

	bIsSelected = bNewSelected;
	this->SetVisibility(bIsSelected);
}
