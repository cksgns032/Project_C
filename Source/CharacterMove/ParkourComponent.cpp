// Fill out your copyright notice in the Description page of Project Settings.


#include "ParkourComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UParkourComponent::UParkourComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UParkourComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UParkourComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UParkourComponent::TraceLege()
{
	AActor* owner = GetOwner();
	FVector Start = FVector(
		owner->GetActorLocation().X,
		owner->GetActorLocation().Y,
		owner->GetActorLocation().Z + (5 * Trace_Vertical) + Initial_Zoffset
	);
	FVector End = (owner->GetActorForwardVector() * Trace_Forward) + Start;

	FHitResult HitResult;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetOwner());

	bool hit = UKismetSystemLibrary::SphereTraceSingle(GetWorld(), Start, End, Trace_Radious, UEngineTypes::ConvertToTraceType(ECC_Visibility),
		false, 
		ActorsToIgnore,										
		EDrawDebugTrace::ForDuration,                       
		HitResult,                                          
		true);

	if (hit)
	{
			//HitResult.ImpactPoint
	}
	UE_LOG(LogTemp, Log, TEXT("TARCE"));
	DrawDebugSphere(GetWorld(), Start, Trace_Radious, 12, FColor::Red);
}

