// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemBox.generated.h"

class UStaticMeshComponent;
class UWidgetComponent;

enum EInteractionType {
	Press,
	Trigger,
};

UCLASS()
class CHARACTERMOVE_API AItemBox : public AActor , public ISearchableInterface
{
	GENERATED_BODY()

protected:
	EInteractionType Type = EInteractionType::Trigger;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	TObjectPtr<UStaticMeshComponent> ItemMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget");
	TObjectPtr <UWidgetComponent> InteractionWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ChargePercent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> RewardActor;
	
public:	
	// Sets default values for this actor's properties
	AItemBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnBegine_Implementation() override;
	virtual void OnTrigger_Implementation() override;
	virtual void OnEnd_Implementation() override;

public:
	UFUNCTION(BlueprintCallable)
	void FullCharge();

};
