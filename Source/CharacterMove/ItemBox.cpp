// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBox.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"


// Sets default values
AItemBox::AItemBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	ItemMesh->SetupAttachment(RootComponent);

	InterectionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Interection Widget"));
	InterectionWidget->SetupAttachment(ItemMesh);

}

// Called when the game starts or when spawned
void AItemBox::BeginPlay()
{
	Super::BeginPlay();
	InterectionWidget->SetHiddenInGame(true, true);
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
	InterectionWidget->SetHiddenInGame(false, false);
}

void AItemBox::OnEnd_Implementation() {
	InterectionWidget->SetHiddenInGame(true, true);
}

void AItemBox::FullCharge()
{
	GetWorld()->SpawnActor<AActor>(RewardActor, GetActorTransform());
	this->Destroy();
}

