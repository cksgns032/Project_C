// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHUD.h"

void AGameHUD::BeginPlay()
{
    Super::BeginPlay();

    if (!HUDWidgetClass) return;

    APlayerController* PC = GetOwningPlayerController();
    if (!PC) return;

    // À§Á¬ »ý¼º
    HUDWidget = CreateWidget<UWidgetHud>(PC, HUDWidgetClass);

    if (HUDWidget)
        HUDWidget->AddToViewport();
}
