// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ParkourComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CHARACTERMOVE_API UParkourComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UParkourComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parkour")
	double Initial_Zoffset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parkour")
	double Trace_Radious;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parkour")
	double Trace_Vertical;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parkour")
	double Trace_Forward;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void TraceLege();
		
};
