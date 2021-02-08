// Fill out your copyright notice in the Description page of Project Settings.


#include "BTSelectPatrolPoint.h"
#include "AIAlphaController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AITargetPoint.h"

EBTNodeResult::Type UBTSelectPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, ::uint8* NodeMemory)
{
    AAIAlphaController* AICon = Cast<AAIAlphaController>(OwnerComp.GetAIOwner());

    if(AICon)
    {
        /*블랙보드 컴포넌트 가져오기*/
        UBlackboardComponent* BlackboardComp = AICon->GetBlackboardComp();

        AAITargetPoint* CurrentPoint = Cast<AAITargetPoint>(BlackboardComp->GetValueAsObject("LocationToGo"));

        /*if(!CurrentPoint)
        {
            UE_LOG(LogTemp, Log, TEXT("failed to get path point"));
        }*/
        
        TArray<AActor*> AvailablePatrolPoints = AICon->GetPatrolPoints();

        AAITargetPoint* NextPatrolPoint = nullptr;

        if(AICon->CurrentPatrolPoint != AvailablePatrolPoints.Num() - 1)
        {
            NextPatrolPoint = Cast<AAITargetPoint>(AvailablePatrolPoints[++AICon->CurrentPatrolPoint]); 
        }
        else //if there is not any more points to go to
        {
            NextPatrolPoint = Cast<AAITargetPoint>(AvailablePatrolPoints[0]);
            AICon->CurrentPatrolPoint = 0;
        }
        //UE_LOG(LogTemp, Log, TEXT("Next path NUM: %d"),AICon->CurrentPatrolPoint);
        BlackboardComp->SetValueAsObject("LocationToGo",NextPatrolPoint);

        return EBTNodeResult::Succeeded;
    }
    return EBTNodeResult::Failed;
}
