// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Settings/PrimaryGameState.h"

APrimaryGameState::APrimaryGameState() {

	// Init

	// Calendar
	Years = 2020;
	Months = 7;
	Days = 25;
	DayOfWeek = 6;
	DayCounter = 0;

	// Clock
	Hours = 0;
	Minutes = 0;
	Seconds = 0;

	// Game Time
	GameDayLength = 600.0f;
	GameSegment = 0.0f;
	GameDay = 0;

	// Game Speed Settings
	/*
	* Real Time : GameSpeed = Time in Game
	* 1s : 1 = 1 Game Hour
	* 1s : 60 = 1 Game Minute
	* 1s : 3600 = Real Time (1s IRL is 1s in game)
	* 1m : 2.5 = 1 Game Day
	* 1hr : 150  = 1 Game Day
	*/

	GameSpeed = 1;

	GameTime = (Hours + (Minutes / float(60.0f)) + (Seconds / float(3600.0f)));
	UE_LOG(LogTemp, Warning, TEXT("Gametime %f"), GameTime);
	DateTimeStruct = (Years, Months, Days, Hours, Minutes, Seconds);

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	ECurrentTimeEvent = EGameTimeEvent::NormalRoutine;
}

void APrimaryGameState::BeginPlay() {

	Super::BeginPlay();

	OnGameTimeUpdated.Broadcast(ECurrentTimeDay);
	OnGameEventUpdated.Broadcast(ECurrentTimeEvent);
}

void APrimaryGameState::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);

	if (GameSpeed != 0) {

		CalculateTime(DeltaTime, GameSpeed, GameTime, GameTime, DayCounter);
		SetClockCalendar();
		SetClockGame();
	}

}

// Methods
void APrimaryGameState::CalculateTime(float DeltaTime, float CurrentGameSpeed, float GameTimeIn, float& GameTimeOut, int& DayCounterOut) {

	if ( ((DeltaTime * CurrentGameSpeed) + GameTimeIn) >= GameDayLength) {
		GameDay += 1;
	}
	GameTime = fmod(((DeltaTime * CurrentGameSpeed) + GameTimeIn), GameDayLength);
	GameTimeOut = GameTime; // For BPs
	DayCounterOut = DayCounter; // For BPs
}

void APrimaryGameState::SetClockCalendar() {

	// Calculate Seconds, Minutes, Hours
	float InitialConversion = GameTime * 3600.0f;
	Seconds = floor(fmod(InitialConversion, 60.0f)); // 0 to 59
	Minutes = floor(fmod(int(InitialConversion / 60.0f), 60.0f));
	Hours = floor(fmod(int((InitialConversion / 60.0f) / 60.0f), 24.0f));

	// Set Calendar
	DayOfWeek += DayCounter;

	if (DayOfWeek > 7) {
		DayOfWeek = 1;
		Days += DayCounter;
	}
	if (Days > DateTimeStruct.DaysInMonth(Years, Months)) {
		Days = 1;
		Months += 1;
	}
	if (Months > 12) {
		Months = 1;
		Years += 1;
	}
	SetDateTime(Years, Months, Days, Hours, Minutes, Seconds);
}

void APrimaryGameState::SetClockGame() {

	GameSegment = (GameTime / 60.0f);

	// Time of Day
	if (GameSegment < 7.5) {
		ECurrentTimeDay = EGameTimeDay::Day;
	}
	else if (GameSegment < 8) {
		ECurrentTimeDay = EGameTimeDay::Dusk;
	}
	else if (GameSegment <= 10) {
		ECurrentTimeDay = EGameTimeDay::Night;
	}

	// Events of Day
	if (GameSegment < 0.5) {
		ECurrentTimeEvent = EGameTimeEvent::MorningWake;
	}
	else if (GameSegment < 4) {
		ECurrentTimeEvent = EGameTimeEvent::NormalRoutine;
	}
	else if (GameSegment < 4.5) {
		ECurrentTimeEvent = EGameTimeEvent::MiddayMeal;
	}
	else if (GameSegment <= 7.5) {
		ECurrentTimeEvent = EGameTimeEvent::NormalRoutine;
	}
	else if (GameSegment <= 10) {
		ECurrentTimeEvent = EGameTimeEvent::EveningBed;
	}

	if (ECurrentTimeDay != EOldTimeDay) {
		OnGameTimeUpdated.Broadcast(ECurrentTimeDay);
	}
	if (ECurrentTimeEvent != EOldTimeEvent) {
		OnGameEventUpdated.Broadcast(ECurrentTimeEvent);
	}

	EOldTimeDay = ECurrentTimeDay;
	EOldTimeEvent = ECurrentTimeEvent;
}

void APrimaryGameState::SetDateTime(UPARAM(ref) int& Year, UPARAM(ref) int& Month, UPARAM(ref) int& Day, UPARAM(ref) int& Hour, UPARAM(ref) int& Minute, UPARAM(ref) int& Second) {

	DateTimeStruct = (Year, Month, Day, Hour, Minute, Second);
}

void APrimaryGameState::GetGameTimeInfo(float& GameSegmentOut, int& GameDayOut) {

	GameSegmentOut = GameSegment;
	GameDayOut = GameDay;
}

void APrimaryGameState::GetGameTimeEvents(EGameTimeDay& GameDayOut, EGameTimeEvent& GameEventOut) {

	GameDayOut = ECurrentTimeDay;
	GameEventOut = ECurrentTimeEvent;
}

void APrimaryGameState::SkipTimeAhead(float RequestedJump, bool ForwardDirection) {

	if (ForwardDirection) {
		APrimaryGameState::GameTime += RequestedJump;
	}
	else {
		APrimaryGameState::GameTime -= RequestedJump;
	}
}
