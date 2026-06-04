// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetHud.h"
#include "RunGameMode.h"
#include "Kismet/GameplayStatics.h"

void UWidgetHud::UpdateSlideProgress(float Percent)
{
	if (Slide_Progress)
		Slide_Progress->SetPercent(Percent);
}

void UWidgetHud::UpdateHookProgress(float Percent)
{
	if (Hook_Progress)
		Hook_Progress->SetPercent(Percent);
}

void UWidgetHud::ResetAllProgress()
{
	if (Slide_Progress)
		Slide_Progress->SetPercent(0.0f);

	if (Hook_Progress)
		Hook_Progress->SetPercent(0.0f);
}

void UWidgetHud::UpdateTimer(float Time)
{
	int32 Minutes = FMath::FloorToInt(Time / 60.0f);
	int32 Seconds = FMath::FloorToInt(
		FMath::Fmod(Time, 60.0f));

	if (Timer_Text)
	{
		Timer_Text->SetText(FText::FromString(
			FString::Printf(TEXT("%02d:%02d"),
				Minutes, Seconds)));
	}
}

void UWidgetHud::NativeConstruct()
{
	Super::NativeConstruct();

	ResetAllProgress();
}
