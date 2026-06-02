// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBox.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AItemBox::AItemBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	ItemMesh->SetupAttachment(RootComponent);

	InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Interection Widget"));
	InteractionWidget->SetupAttachment(ItemMesh);

}

// Called when the game starts or when spawned
void AItemBox::BeginPlay()
{
	Super::BeginPlay();
	InteractionWidget->SetHiddenInGame(true, true);
	ChargePercent = 0.f;
}

// Called every frame
void AItemBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemBox::OnBegine_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("BOX"));
	InteractionWidget->SetHiddenInGame(false, false);
}

void AItemBox::OnTrigger_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("BOX Trigger"));
	ChargePercent += UGameplayStatics::GetWorldDeltaSeconds(GetWorld())*3;
}

void AItemBox::OnEnd_Implementation() {
	InteractionWidget->SetHiddenInGame(true, true);
}

void AItemBox::FullCharge()
{
	GetWorld()->SpawnActor<AActor>(RewardActor, GetActorTransform());
	this->Destroy();
}

