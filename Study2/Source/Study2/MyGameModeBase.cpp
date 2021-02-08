// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "UnrealCPPHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"

AMyGameModeBase::AMyGameModeBase() : Super()
{
    PrimaryActorTick.bCanEverTick = true;
    // set default pawn class to our Blueprinted character
   // static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/DronePawn"));
   // DefaultPawnClass = PlayerPawnClassFinder.Class;

    // use our custom HUD class
    HUDClass = AUnrealCPPHUD::StaticClass();
}

void AMyGameModeBase::BeginPlay()
{
    Super::BeginPlay();
   // SetCurrentState(EGamePlayState::EPlaying);
    MyCharacter = Cast<ADronePawn>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void AMyGameModeBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if(MyCharacter)
    {
        if(FMath::IsNearlyZero(MyCharacter->GetHealth(), 0.001f))
        {
            //SetCurrentState(EGamePlayState::EGameOver);
            
        }
    }
}

/*EGamePlayState AMyGameModeBase::GetCurrentState() const
{
    return CurrentState;
}

void AMyGameModeBase::SetCurrentState(EGamePlayState NewState)
{
    CurrentState = NewState;
    HandleNewState(CurrentState);
}

void AMyGameModeBase::HandleNewState(EGamePlayState NewState)
{
    switch (NewState)
    {
    case EGamePlayState::EPlaying:
        {
            // do nothing
        }
        break;
        // Unknown/default state
        case EGamePlayState::EGameOver:
            {
                UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
            }
        break;
        // Unknown/default state
        default:
        case EGamePlayState::EUnknown:
            {
                // do nothing
            }
        break;
    }
}*/