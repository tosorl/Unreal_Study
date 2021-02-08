// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "targetActor.generated.h"

UCLASS()
class UNREALSTUDY2_API AtargetActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AtargetActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UPROPERTY(EditAnywhere)
    UStaticMeshComponent* targetMesh;

	virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp,
							bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse,
							const FHitResult& Hit) override;
	
	UPROPERTY(EditAnywhere)
	int32 AttackedPoint;

	UFUNCTION(BlueprintPure)
	int32 GetPoint();\

	FTimerHandle SpawnTimerHandle;
	
};
