// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Enums/EndlingDetails/EndlingBuildingType.h"
#include "Core/Enums/EndlingDetails/EndlingBuildingGroup.h"
#include "StructureEndlingBuilding.generated.h"



USTRUCT(BlueprintType)
struct FEndlingBuildingDetails
{

	GENERATED_BODY()

	UPROPERTY(editAnywhere, BlueprintReadWrite)
	EEndlingBuildingType BuildingType;

	UPROPERTY(editAnywhere, BlueprintReadWrite)
	EEndlingBuildingGroup BuildingGroup;

	// Default Constructor
	FEndlingBuildingDetails() {
		BuildingType = EEndlingBuildingType::Stockpile;
		BuildingGroup = EEndlingBuildingGroup::Storage;
	}

};