// Fill out your copyright notice in the Description page of Project Settings.


#include "RunGameMode.h"
#include "Kismet/GameplayStatics.h"

//ARunGameMode::ARunGameMode()
//{
//}

void ARunGameMode::StartPlay()
{
    Super::StartPlay();

    SetPlayerInput(false);
    CurrentState = EGameState::Waiting;
    
    GetWorld()->GetTimerManager().SetTimer(StartHandle, [this]() {
        UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD();
        SetPlayerInput(true);
        CurrentState = EGameState::Playing;
        },10,false);
}

void ARunGameMode::PostLogin(APlayerController* PC)
{
    Super::PostLogin(PC);
}

void ARunGameMode::SetPlayerInput(bool value)
{
    APlayerController* PC =
        UGameplayStatics::GetPlayerController(
            GetWorld(), 0);
    if (!PC) return;

    if (value)
        PC->EnableInput(PC);
    else
        PC->DisableInput(PC);
}
