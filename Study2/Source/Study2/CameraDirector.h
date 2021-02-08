// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraDirector.generated.h"

USTRUCT(Atomic)
struct Fcamst {
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere)
		AActor* Cam;
	UPROPERTY(EditAnywhere)
		float view_time;
};

UCLASS()
class STUDY2_API ACameraDirector : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameraDirector();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		TArray<Fcamst> CamArr;
	/*	AActor* CameraOne;
	UPROPERTY(EditAnywhere)
		AActor* CameraTwo*/
	int index;
	float TimeToNextCameraChange;

};
