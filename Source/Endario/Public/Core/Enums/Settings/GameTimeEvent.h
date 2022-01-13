// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EGameTimeEvent: uint8 {
    MorningWake = 0        UMETA(DisplayName = "MorningWake"),
    MiddayMeal = 1        UMETA(DisplayName = "MiddayMeal"),
    EveningBed = 2    UMETA(DisplayName = "EveningBed"),
    NormalRoutine = 3    UMETA(DisplayName = "NormalRoutine"),
};