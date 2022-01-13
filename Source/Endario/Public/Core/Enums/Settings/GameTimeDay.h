// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EGameTimeDay: uint8 {
    Day = 0        UMETA(DisplayName = "Day"),
    Dusk = 1        UMETA(DisplayName = "Dusk"),
    Night = 2    UMETA(DisplayName = "Night"),
};