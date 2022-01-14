// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EEndlingClass : uint8 {
    Unassigned = 0        UMETA(DisplayName = "Unassigned"),
    Lumberjack = 1        UMETA(DisplayName = "Lumberjack"),
    Miner = 2             UMETA(DisplayName = "Miner"),
    Gatherer = 3          UMETA(DisplayName = "Food Gatherer"),
    Woodworker = 4        UMETA(DisplayName = "Woodworker"),
    Stonemason = 5        UMETA(DisplayName = "Stonemason"),
    Cook = 6              UMETA(DisplayName = "Cook"),
};
