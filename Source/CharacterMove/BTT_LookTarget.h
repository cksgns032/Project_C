// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_LookTarget.generated.h"

/**
 * 
 */
UCLASS()
class CHARACTERMOVE_API UBTT_LookTarget : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTT_LookTarget();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	
};
