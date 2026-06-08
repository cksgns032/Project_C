// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SearchableInterface.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemKey.generated.h"

UCLASS()
class CHARACTERMOVE_API AItemKey : public AActor, public ISearchableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemKey();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	TObjectPtr<USphereComponent> Collision;
public:
	virtual void OnBegine_Implementation() override;
};
