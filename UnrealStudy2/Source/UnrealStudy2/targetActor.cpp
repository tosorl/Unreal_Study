// Fill out your copyright notice in the Description page of Project Settings.


#include "targetActor.h"


#include "UnrealStudy2Character.h"
#include "UnrealStudy2Projectile.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AtargetActor::AtargetActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	targetMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("theMesh"));
	RootComponent = targetMesh;

	AttackedPoint = 100;
}

// Called when the game starts or when spawned
void AtargetActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AtargetActor::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* bullet = Cast<AUnrealStudy2Projectile>(Other);
	if(bullet != NULL)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hit!"));
		AUnrealStudy2Character* CurrentPlayer = Cast<AUnrealStudy2Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
		if(CurrentPlayer != NULL)
		{
			CurrentPlayer->SetScore(AttackedPoint);
		}
		Destroy();
	}
}

int32 AtargetActor::GetPoint()
{
	return AttackedPoint;
}

