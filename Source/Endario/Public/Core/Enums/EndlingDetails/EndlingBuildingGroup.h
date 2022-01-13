// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EEndlingBuildingGroup: uint8 {
    Routine = 0       UMETA(DisplayName = "Routine"),
    Storage = 1       UMETA(DisplayName = "Storage"),
    Refiner = 2       UMETA(DisplayName = "Refiner"),
    Crafter = 3       UMETA(DisplayName = "Crafter"),
    Creator = 4       UMETA(DisplayName = "Creator"),
    Service = 5       UMETA(DisplayName = "Service"),
    Utility = 6       UMETA(DisplayName = "Utility"),
    Researcher = 7    UMETA(DisplayName = "Researcher"),
    Combat = 8        UMETA(DisplayName = "Combat"),
};