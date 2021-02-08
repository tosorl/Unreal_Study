// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotatingActor.generated.h"

UCLASS()
class STUDY2_API ARotatingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARotatingActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	float AngleAxis;

	UPROPERTY(EditAnywhere, Category=Movement)
	FVector Dimensions;
	UPROPERTY(EditAnywhere, Category=Movement)
	FVector AxisVector;
	UPROPERTY(EditAnywhere,Category=Movement)
	float Multiplier;

	UPROPERTY(EditAnywhere)
	APawn *Target;
	UPROPERTY(EditAnywhere)
	UStaticMesh* shape;

	//스폰 시간 설정
	UPROPERTY(EditAnywhere)
	int32 CountdownTimer;

	// 타이머 핸들러
	FTimerHandle CountdownTimerHandle;

	//타이머 함수
	void Counting();
	
	bool IsSpawn;

	UPROPERTY()
	UStaticMeshComponent* Child[3];
	
	UFUNCTION()
	static void SpawnMesh();
};
