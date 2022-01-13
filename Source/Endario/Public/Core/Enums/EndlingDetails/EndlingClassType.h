// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EEndlingClassType : uint8 {
    Harvester = 0        UMETA(DisplayName = "Harvester"),
    Refiner = 1        UMETA(DisplayName = "Refiner"),
};