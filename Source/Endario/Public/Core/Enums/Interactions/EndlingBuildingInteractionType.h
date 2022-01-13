// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EEndlingBuildingInteractionType : uint8 {
    Outer = 0        UMETA(DisplayName = "Outer"),
    Inner = 1        UMETA(DisplayName = "Inner"),
    Fixed = 2    UMETA(DisplayName = "Fixed"),
    Vanish = 2    UMETA(DisplayName = "Vanish"),
};