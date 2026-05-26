// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_ResetAttackCoolTime.h"

#include "BehaviorTree/BlackboardComponent.h"


UBTT_ResetAttackCoolTime::UBTT_ResetAttackCoolTime()
{
	NodeName = TEXT("Reset Attack CoolTime");
}

EBTNodeResult::Type UBTT_ResetAttackCoolTime::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(GetSelectedBlackboardKey(),3);

	return EBTNodeResult::Succeeded;
}