// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EEndlingSubtype : uint8 {
    Primary = 0        UMETA(DisplayName = "Temporary 1"),
    Secondary = 1    UMETA(DisplayName = "Temporary 2"),
    Tertiary = 2    UMETA(DisplayName = "Temporary 3")
};