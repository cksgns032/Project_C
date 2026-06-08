// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemKey.h"
#include "Components/SphereComponent.h"
#include "RogueCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "RogueCharacter.h"

// Sets default values
AItemKey::AItemKey()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	RootComponent= Collision;
}

// Called when the game starts or when spawned
void AItemKey::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemKey::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AItemKey::OnBegine_Implementation()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PC)
	{
		ARogueCharacter* Character = Cast<ARogueCharacter>(PC->GetCharacter());
		if (Character && Character->HasKey() == false)
		{
			Character->SetKey(true);
			Destroy();
		}
	}
}
