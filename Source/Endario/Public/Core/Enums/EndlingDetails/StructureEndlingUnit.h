// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Enums/EndlingDetails/EndlingGender.h"
#include "Core/Enums/EndlingDetails/EndlingClass.h"
#include "StructureEndlingUnit.generated.h"



USTRUCT(BlueprintType)
struct FEndlingUnitDetails
{

	GENERATED_BODY()

	UPROPERTY(editAnywhere, BlueprintReadWrite)
	FString UnitFirstName;
	UPROPERTY(editAnywhere, BlueprintReadWrite)
	FString UnitLastName;

	UPROPERTY(editAnywhere, BlueprintReadWrite)
	EEndlingGender UnitGender;
	UPROPERTY(editAnywhere, BlueprintReadWrite)
	EEndlingClass UnitClass;
	UPROPERTY(editAnywhere, BlueprintReadWrite)
	TArray<int32> UnitOcean;

	// Default Constructor
	FEndlingUnitDetails() {
		UnitFirstName = "First. Temp";
		UnitLastName = "Last. Temp";
		//UnitGender = "Gender. Temp";
		//UnitClass = "Class. Temp";
		//UnitGender = "Gender. Temp";
		//UnitClass = "Class. Temp";
		UnitOcean = { 0, 0, 0, 0, 0 };
	}

};