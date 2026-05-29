// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetHud.h"

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

void UWidgetHud::NativeConstruct()
{
	Super::NativeConstruct();

	ResetAllProgress();
}
