// Fill out your copyright notice in the Description page of Project Settings.


#include "PingActor.h"

// Sets default values
APingActor::APingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	_mesh->SetWorldScale3D(FVector(0.3f));
	_mesh->SetRelativeLocation(FVector(0.0f,0.0f,10.0f));
	_mesh->SetRelativeRotation(FRotator(0.0f,0.0f,180.0f));
	RootComponent = _mesh;
}

// Called when the game starts or when spawned
void APingActor::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(LifeTime);
}

// Called every frame
void APingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/*void APingActor::LifeTimer()
{
	LifeTime--;
	if(LifeTime<1)
	{
		
	}
}*/
