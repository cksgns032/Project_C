// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget_GameState.h"
#include "RunGameMode.h"

void UWidget_GameState::ShowGameStateText()
{
	ARunGameMode* GameMode = Cast<ARunGameMode>(GetWorld()->GetAuthGameMode());
	FString Str_State;
	if (GameMode)
	{
		EGameState state = GameMode->GetState();
		switch (state)
		{
		case EGameState::Waiting:
			Str_State = "Waiting";
			break;
		case EGameState::Countdown:
			Str_State = "CountDown";
			break;
		case EGameState::Playing:
			Str_State = "Play";
			break;
		case EGameState::GameOver:
			Str_State = "GameOver";
			break;
		case EGameState::Clear:
			Str_State = "Clear";
			break;
		}

		if (GameState_Text)
		{
			GameState_Text->SetText(FText::FromString(Str_State));
		}
	}
}
