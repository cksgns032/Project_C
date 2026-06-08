// Fill out your copyright notice in the Description page of Project Settings.


#include "RunGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "AIEnemy.h"
#include "GameHUD.h"
#include "ItemBox.h"

//ARunGameMode::ARunGameMode()
//{
//}

void ARunGameMode::StartPlay()
{
    Super::StartPlay();

    APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    GameHud = Cast<AGameHUD>(PC->GetHUD());

    // 변수 초기화
    EnemyCnt = 0;
    CurKey = 0;

    UpdateKeyScore();

    CurrentState = EGameState::Waiting;
    GameHud->ShowGameState();

    //return;

    // 상자 위치 확보
    TArray<AActor*> SpawnPoints;
    UGameplayStatics::GetAllActorsOfClass(
        GetWorld(),
        SpawnPointClass,
        SpawnPoints
    );

    for (AActor* Point : SpawnPoints)
    {
        SpawnLocations.Add(Point->GetActorLocation());
    }

    this->SetPlayerInput(false);

    GameTime = 90.0f;

    GameHud->HUDWidget->UpdateTimer(GameTime);
    
    GetWorld()->GetTimerManager().SetTimer(StartHandle, [this]() {
        UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD();
        SetPlayerInput(true);
        
        //SpawnEnemy();
        //GamePlay();

        GetWorld()->GetTimerManager().SetTimer(
            SpawnTimer,
            this,
            &ARunGameMode::SpawnActors,
            SpawnInterval,
            false
        );
        
        CurrentState = EGameState::Playing;
        GameHud->GameStateWidget->RemoveFromParent();
        UE_LOG(LogTemp, Log, TEXT("Start"));
        },3,false);
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

    ACharacter* Character = Cast<ACharacter>(PC->GetPawn());

    if (value)
    {
        PC->EnableInput(PC);

        // 이동 복구
        if (Character)
        {
            Character->GetCharacterMovement()
                ->SetMovementMode(MOVE_Walking);
        }
    }
    else
    {
        PC->DisableInput(PC);

        if (Character)
        {
            Character->GetCharacterMovement()
                ->StopMovementImmediately();
            Character->GetCharacterMovement()
                ->DisableMovement();
        }
    }
}

void ARunGameMode::AddKey()
{
    CurKey = FMath::Min(CurKey + 1, MaxKey);
    UpdateKeyScore();
    if (CurKey == MaxKey)
    {
        CurrentState = EGameState::Clear;
        GameOver();
    }
}

void ARunGameMode::UpdateKeyScore()
{
    GameHud->HUDWidget->UpdateKey(CurKey, MaxKey);
}

void ARunGameMode::SpawnEnemy()
{
    GetWorld()->GetTimerManager().SetTimer(SpawnHandle, [this] 
        {
            if (EnemyClass)
            {
                APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
                
                FVector SpawnLocation= PC->GetCharacter()->GetActorLocation();
                SpawnLocation.X = UKismetMathLibrary::RandomFloatInRange(SpawnLocation.X - 300, SpawnLocation.X + 300);
                SpawnLocation.Y = UKismetMathLibrary::RandomFloatInRange(SpawnLocation.Y - 300, SpawnLocation.Y + 300);
                
                FTransform EnemyTransform;
                EnemyTransform.SetLocation(SpawnLocation);
                EnemyTransform.SetRotation(FQuat::Identity);
                EnemyTransform.SetScale3D(FVector::OneVector);
                
                FActorSpawnParameters Params;
                Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

                GetWorld()->SpawnActor<AAIEnemy>(EnemyClass, EnemyTransform, Params);

                EnemyCnt++;
            }
            if (EnemyCnt >= 10)
            {
                GetWorld()->GetTimerManager().ClearTimer(SpawnHandle);
            }
        }, 3.0f, true);
}

void ARunGameMode::SpawnActors()
{
    if (!SpawnActor) return;
    if (SpawnLocations.Num() == 0) return;

    // 랜덤 위치 선택
    int32 RandomIndex = FMath::RandRange(
        0, SpawnLocations.Num() - 1);

    FVector SpawnLocation = SpawnLocations[RandomIndex];

    FActorSpawnParameters Params;
    Params.SpawnCollisionHandlingOverride =
        ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    GetWorld()->SpawnActor<AItemBox>(
        SpawnActor,
        SpawnLocation,
        FRotator::ZeroRotator,
        Params
    );
}

void ARunGameMode::GamePlay()
{
    // 1초마다 감소
    GetWorld()->GetTimerManager().SetTimer(
        GameTimerHandle,
        [this]()
        {
            if (!IsValid(this)) return;

            GameTime -= 1.0f;
            if (GameHud)
            {
                GameHud->HUDWidget->UpdateTimer(GameTime);
                if (GameTime <= 0.0f)
                {
                    GameTime = 0.0f;
                    GetWorld()->GetTimerManager()
                        .ClearTimer(GameTimerHandle);
                    CurrentState = EGameState::GameOver;
                    GameOver(); // 시간 종료
                }
            }

        },
        1.0f, true
    );
}

void ARunGameMode::GameOver()
{   
    SetPlayerInput(false);
    GetWorld()->GetTimerManager()
        .ClearTimer(GameTimerHandle);
    GameHud->ShowGameState();
    UE_LOG(LogTemp, Log, TEXT("Game Over"));
}
