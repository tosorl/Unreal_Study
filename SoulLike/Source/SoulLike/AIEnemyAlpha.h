// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/PawnSensingComponent.h"
#include "AIEnemyAlpha.generated.h"

UCLASS()
class SOULLIKE_API AAIEnemyAlpha : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAIEnemyAlpha();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//행동 트리 변수
	UPROPERTY(EditAnywhere, Category= AI)
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(VisibleAnywhere, Category= AI)
	class UPawnSensingComponent* PawnSensingComp;

	UFUNCTION(BlueprintPure)
	float GetHealthP();

private:

	UFUNCTION()
	void OnPlayerCaught(APawn* Pawn);

	UCharacterMovementComponent* AIMovement;

	float MaxHealth;
	float CurrentHealth;
	
};
