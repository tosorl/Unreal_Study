// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SphereComponent.h"
#include "PingActor.h"
#include "DronePawn.generated.h"

UCLASS()
class STUDY2_API ADronePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADronePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//입력 변수
	FVector2D MovementInput;
	FVector2D CameraInput;
	float ZoomFactor;
	bool bZoomingIn;
	bool Is_Running;
	bool DroneActive;

	//Follower
	UPROPERTY(EditAnywhere)
	APawn * Target_Person;
	//height
	UPROPERTY(EditAnywhere)
	float Flight_Height;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> Ping_BP;
	
	//health property
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health")
	float FullHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health")
	float Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health")
	float HealthPercentage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health")
	float PrevHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health")
	float DMG_dot;

	//health Func
	UFUNCTION(BlueprintPure, Category = "Health")
    float GetHealth();
	UFUNCTION(BlueprintCallable, Category = "Health")
    void UpdateHealth(float HealthChange);
	
	//입력 함수
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void PitchCamera(float AxisValue);
	void YawCamera(float AxisValue);
	void ZoomIn();
	void ZoomOut();
	void IsRunning();
	void IsntRunning();
	void Active_trig();
	void PerformRaycast();
	protected:
	UPROPERTY(EditAnywhere)
	USpringArmComponent* OurCameraSpringArm;
	UCameraComponent* OurCamera;

};
