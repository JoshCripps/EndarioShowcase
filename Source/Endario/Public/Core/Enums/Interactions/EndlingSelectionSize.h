// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EEndlingSelectionSize : uint8 {
    Character = 0        UMETA(DisplayName = "Character"),
    SmallBuilding = 1     UMETA(DisplayName = "SmallBuilding"),
    MediumBuilding = 2    UMETA(DisplayName = "MediumBuilding"),
    LargeBuilding = 3    UMETA(DisplayName = "LargeBuilding"),
    SmallResource = 4    UMETA(DisplayName = "SmallResource"),
    MediumResource = 5    UMETA(DisplayName = "MediumResource"),
};