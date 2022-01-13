// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EEndlingBuildingType : uint8 {
    Hearth = 0    UMETA(DisplayName = "Hearth"),
    Stockpile = 1        UMETA(DisplayName = "Stockpile"),
    BuildersYard = 2        UMETA(DisplayName = "Warehouse"),
    Granary = 3        UMETA(DisplayName = "Granary"),
    Lumbermill = 4    UMETA(DisplayName = "Lumbermill"),
    MasonHouse = 5    UMETA(DisplayName = "Masons Yard"),
    Kitchen = 6    UMETA(DisplayName = "Kitchen"),
    House = 7    UMETA(DisplayName = "House"),
};