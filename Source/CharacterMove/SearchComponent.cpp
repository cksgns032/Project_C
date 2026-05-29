// Fill out your copyright notice in the Description page of Project Settings.

#include "SearchComponent.h"
#include "SearchableInterface.h"
#include "Components/SphereComponent.h"

// Sets default values for this component's properties
USearchComponent::USearchComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


	SearchCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SearchCollider"));
	SearchCollider->SetSphereRadius(100);
	// ...
}


// Called when the game starts
void USearchComponent::BeginPlay()
{
	Super::BeginPlay();

	if (SearchCollider && GetOwner() != nullptr)
	{
		SearchCollider->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		SearchCollider->OnComponentBeginOverlap.AddDynamic(this, &USearchComponent::BeginEvent);
	}
	// ...
	
}


// Called every frame
void USearchComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USearchComponent::BeginEvent(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->Implements<USearchableInterface>())
	{
		UE_LOG(LogTemp, Log, TEXT("CO"));

		ISearchableInterface::Execute_OnBegine(OtherActor);
	}
}

