// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/TextRenderComponent.h"
#include "Countdown.generated.h" // .generated.h�� �׻� ��� ������ ���� �������� �־�� �Ѵ�.


UCLASS()
class STUDY2_API ACountdown : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACountdown();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	//�� ������ ī��Ʈ�ٿ� ���� �ð��Դϴ�.
	UPROPERTY(EditAnywhere)
	int32 CountdownTime;
	int32 burningtime;
	UTextRenderComponent* CountdownText;
	UPROPERTY(BlueprintReadOnly)
	FTimerHandle FuelTimer;
	FTimerHandle CountdownTimerHandle;
	UPROPERTY(EditAnywhere)
		FRotator target;
	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* OurParticleSystem;
	
	void UpdateTimerDisplay();
	void AdvanceTimer();
	void AdvanceTimer2();
	void burning();
	UFUNCTION(BlueprintNativeEvent)
	void CountdownHasFinished();
	virtual void CountdownHasFinished_Implementation();

	UFUNCTION(BlueprintNativeEvent)
	void AddFuel();
	virtual void AddFuel_Implementation();
	void DouseWithWater();
};
