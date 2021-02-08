// Fill out your copyright notice in the Description page of Project Settings.


#include "AIEnemyAlpha.h"
#include "AIAlphaController.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AAIEnemyAlpha::AAIEnemyAlpha()
{
	// npc 시야 적용 컴포넌트 추가
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	PawnSensingComp->SetPeripheralVisionAngle(60.f);
	PawnSensingComp->SightRadius = 1000.f;
	
	AIMovement =  GetCharacterMovement();
	AIMovement->MaxWalkSpeed *= 0.6f;

	MaxHealth = 100.f;
	CurrentHealth = 75.f;
}

// Called when the game starts or when spawned
void AAIEnemyAlpha::BeginPlay()
{
	Super::BeginPlay();
	if(PawnSensingComp)
	{
		PawnSensingComp->OnSeePawn.AddDynamic(this,&AAIEnemyAlpha::OnPlayerCaught);
	}
}

// Called to bind functionality to input
void AAIEnemyAlpha::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAIEnemyAlpha::OnPlayerCaught(APawn* Pawn)
{
	/*플레이어 컨트롤러 참조*/
	AAIAlphaController* AIController = Cast<AAIAlphaController>(GetController());

	if(AIController)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5., FColor::Red, TEXT("You have been caught!"));
		AIController->SetPlayerCaught(Pawn);
	}
}

float AAIEnemyAlpha::GetHealthP()
{
	return CurrentHealth / MaxHealth;
}
