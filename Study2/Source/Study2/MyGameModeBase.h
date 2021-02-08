// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DronePawn.h"
#include "MyGameModeBase.generated.h"

//enum to store the current state of gameplay
/*UENUM()
enum class EGamePlayState : uint8
{
	EPlaying 	UMETA(DisplayName = "Playing"),
	EGameOver 	UMETA(DisplayName = "GameOver"),
	EUnknown 	UMETA(DisplayName = "Unknown")
};*/
/**
 * 
 */
UCLASS()
class STUDY2_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AMyGameModeBase();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	ADronePawn* MyCharacter;

	//Return the current playing state
	//UFUNCTION(BlueprintPure, Category="Health")
	//EGamePlayState GetCurrentState() const;

	//Sets a new playing state
	//void SetCurrentState(EGamePlayState NewState);

//private:
	//Keeps track of the current playing state
	//EGamePlayState CurrentState;

	//Handle any function calls that rely upon changing the playing state of our game
	//void HandleNewState(EGamePlayState NewState);
};
