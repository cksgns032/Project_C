// Fill out your copyright notice in the Description page of Project Settings.

#include "BTS_CheckDistance.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"

UBTS_CheckDistance::UBTS_CheckDistance()
{
	NodeName = TEXT("Target Distance Check");
}

void UBTS_CheckDistance::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn == nullptr || OwnerComp.GetAIOwner() == nullptr)
	{
		return;
	}
	float CurrentCoolTime = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(GetSelectedBlackboardKey());
	float worldTime = GetWorld()->DeltaTimeSeconds;
	CurrentCoolTime -= worldTime;
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(GetSelectedBlackboardKey(), CurrentCoolTime);
}
