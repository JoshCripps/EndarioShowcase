// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EEndlingType : uint8 {
    Unit = 0        UMETA(DisplayName = "Unit"),
    Building = 1    UMETA(DisplayName = "Building"),
    Resource = 2    UMETA(DisplayName = "Resource"),
    None = 3        UMETA(DisplayName = "No Type: Error"),
};