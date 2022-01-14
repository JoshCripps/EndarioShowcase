// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Misc/DateTime.h"
#include "Core/Enums/Settings/GameTimeDay.h"
#include "Core/Enums/Settings/GameTimeEvent.h"
#include "PrimaryGameState.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGameTimeUpdate, EGameTimeDay, EDelegatedTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGameEventUpdate, EGameTimeEvent, EDelegatedEvent);


UCLASS()
class ENDARIO_API APrimaryGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	// Constructor
	APrimaryGameState();

protected:
	// Beginplay
	virtual void BeginPlay() override;

public:
	// Tick
	virtual void Tick(float DeltaTime) override;


// Attributes
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Calender")
	int Years;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Calender")
	int Months;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Calender")
	int Days;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Calender")
	int DayOfWeek;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Calender")
	int DayCounter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Clock")
	int Hours;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Clock")
	int Minutes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Clock")
	int Seconds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Clock")
	float GameDayLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Clock")
	float GameSegment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Clock")
	int GameDay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Events")
	EGameTimeDay ECurrentTimeDay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Events")
	EGameTimeEvent ECurrentTimeEvent;

	EGameTimeDay EOldTimeDay;
	EGameTimeEvent EOldTimeEvent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Speed Settings")
	float GameSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Speed Settings")
	float GameTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Speed Settings")
	FDateTime DateTimeStruct;

	// Delegates
	UPROPERTY(BlueprintAssignable, Category = "Game Time Event")
	FGameTimeUpdate OnGameTimeUpdated;

	UPROPERTY(BlueprintAssignable, Category = "Game Time Event")
	FGameEventUpdate OnGameEventUpdated;

public:

	// Methods
	UFUNCTION(BlueprintCallable, Category = "Game Time")
	virtual void CalculateTime(float DeltaTime, float CurrentGameSpeed, float GameTimeIn, float& GameTimeOut, int& DayCounterOut);

	UFUNCTION(BlueprintCallable, Category = "Game Time")
	virtual void SetClockCalendar();

	UFUNCTION(BlueprintCallable, Category = "Game Time")
	virtual void SetClockGame();

	UFUNCTION(BlueprintCallable, Category = "Game Time") // For Normal Pass By Ref Below in UE!!
	virtual void SetDateTime(UPARAM(ref) int &Year, UPARAM(ref) int& Month, UPARAM(ref) int& Day, UPARAM(ref) int& Hour, UPARAM(ref) int& Minute, UPARAM(ref) int& Second);

	// Getters
	UFUNCTION(BlueprintCallable, Category = "Game Time")
	virtual void GetGameTimeInfo(float& GameSegmentOut, int& GameDayOut);

	UFUNCTION(BlueprintCallable, Category = "Game Time")
	virtual void GetGameTimeEvents(EGameTimeDay& GameDayOut, EGameTimeEvent& GameEventOut);

	// Utility
	UFUNCTION(BlueprintImplementableEvent, Category = "Game Time") // For Normal Pass By Ref Below in UE!!
	void GameTimeUpdate();

	UFUNCTION(BlueprintCallable, Category = "Game Time")
	virtual void SkipTimeAhead(float RequestedJump, bool FowardDirection);
};
