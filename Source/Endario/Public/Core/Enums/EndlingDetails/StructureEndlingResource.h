// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructureEndlingResource.generated.h"

USTRUCT(BlueprintType)
struct FEndlingResourceDetails
{

	GENERATED_BODY()

	UPROPERTY(editAnywhere, BlueprintReadWrite)
	FString UnitResourceName;

	// Default Constructor
	FEndlingResourceDetails() {
		UnitResourceName = "Resource. Temp";
	}

};