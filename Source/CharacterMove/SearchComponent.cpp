// Fill out your copyright notice in the Description page of Project Settings.

#include "SearchComponent.h"
#include "SearchableInterface.h"
#include "Components/SphereComponent.h"
#include "SearchableInterface.h"

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
		SearchCollider->OnComponentEndOverlap.AddDynamic(this, &USearchComponent::EndEvent);
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
	UE_LOG(LogTemp, Log, TEXT("%s"),*OtherActor->GetName());
	if (OtherActor->Implements<USearchableInterface>())
	{
		//UE_LOG(LogTemp, Log, TEXT("CO"));

		if (ItemInterface)
		{
			ISearchableInterface::Execute_OnEnd(ItemInterface->_getUObject());
			ItemInterface = nullptr;
		}

		ItemInterface = OtherActor;
		ISearchableInterface::Execute_OnBegine(OtherActor);
		
		UE_LOG(LogTemp, Log, TEXT("Get Box"));
	}
}

void USearchComponent::EndEvent(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (ItemInterface.GetObject() == nullptr)
		return;


	if (OtherActor->Implements<USearchableInterface>())
	{
		ISearchableInterface* OutItem = Cast<ISearchableInterface>(OtherActor);
		ISearchableInterface::Execute_OnEnd(OtherActor);
		UE_LOG(LogTemp, Log, TEXT("Out Box"));
		if (OutItem && ItemInterface.GetObject() == OtherActor)
		{
			ItemInterface = nullptr;
		}
	}

}

