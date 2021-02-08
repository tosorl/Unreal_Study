// Fill out your copyright notice in the Description page of Project Settings.


#include "AIAlphaController.h"

#include "AIEnemyAlpha.h"
#include "AITargetPoint.h"
#include "Kismet/GameplayStatics.h"

AAIAlphaController::AAIAlphaController()
{
    /*블랙보드 와 행동트리 초기화*/
    BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
    BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));

    /*블랙보드 키 초기화*/
    PlayerKey = "Target";
    LocationToGoKey = "LocationToGo";

    CurrentPatrolPoint = 0;
}

void AAIAlphaController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    /*캐릭터 참조*/
    AAIEnemyAlpha* AICharacter = Cast<AAIEnemyAlpha>(InPawn);

    if(AICharacter)
    {
        if(AICharacter->BehaviorTree->BlackboardAsset)
        {
            UE_LOG(LogTemp, Log, TEXT("Success to get blackboard"));
            BlackboardComp->InitializeBlackboard(*(AICharacter->BehaviorTree->BlackboardAsset));
        }

        //경로 포인트 설정
        UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAITargetPoint::StaticClass(),PatrolPoint);
        if(PatrolPoint.Num() > 0)
        {
            UE_LOG(LogTemp, Log, TEXT("Success to get path actors"));
            /*for (AActor* Element : PatrolPoint)
            {
                UE_LOG(LogTemp, Log, TEXT("Path Location: %s"),*(Element->GetActorLocation().ToString()));
            }  */  
        }
        
        
        BehaviorComp->StartTree(*AICharacter->BehaviorTree);
    }
}

void AAIAlphaController::SetPlayerCaught(APawn* InPawn)
{
    if(BlackboardComp)
    {
        BlackboardComp->SetValueAsObject(PlayerKey, InPawn);
    }
}
