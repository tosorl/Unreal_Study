// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIAlphaController.generated.h"

/**
 * 
 */
UCLASS()
class SOULLIKE_API AAIAlphaController : public AAIController
{
	GENERATED_BODY()

	// 행동트리 컴포넌트
	UBehaviorTreeComponent* BehaviorComp;

	//블랙보드 컴포넌트
	UBlackboardComponent* BlackboardComp;

	/*블랙보드 키*/
	UPROPERTY(EditDefaultsOnly, Category= AI)
	FName LocationToGoKey;

	UPROPERTY(EditDefaultsOnly, Category= AI)
	FName PlayerKey;

	TArray<AActor*> PatrolPoint;

	virtual void OnPossess(APawn* InPawn) override;

	
public:

	AAIAlphaController();
	int32 CurrentPatrolPoint;
	void SetPlayerCaught(APawn * InPawn);
	
	/*인라인 GET 함수*/
	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }
	FORCEINLINE TArray<AActor*> GetPatrolPoints() const { return PatrolPoint; }
};
