// Fill out your copyright notice in the Description page of Project Settings.


#include "RotatingActor.h"

// Sets default values
ARotatingActor::ARotatingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Dimensions = FVector(300,0,0);
	AxisVector = FVector(0,0,1);
	Multiplier = 100.0f;
	CountdownTimer = 3;
	IsSpawn = false;
}

// Called when the game starts or when spawned
void ARotatingActor::BeginPlay()
{
	Super::BeginPlay();
	SpawnMesh();
	
}

// Called every frame
void ARotatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = Target->GetActorLocation();
	//UE_LOG(LogTemp,Log, (TEXT("Target Location :: %s"),(Target->GetActorLocation().ToString())))
	AngleAxis += DeltaTime * Multiplier;

	if(AngleAxis >=360.0f)
	{
		AngleAxis = 0;
	}

	FVector RotateValue = Dimensions.RotateAngleAxis(AngleAxis,AxisVector);

	NewLocation.X +=RotateValue.X;
	NewLocation.Y += RotateValue.Y;
	NewLocation.Z += RotateValue.Z;

	FRotator NewRotation = FRotator(0,AngleAxis,0);
	FQuat QuatRotation = FQuat(NewRotation);
	SetActorLocationAndRotation(NewLocation,QuatRotation,false,0,ETeleportType::None);
}

void ARotatingActor::SpawnMesh()
{
	if(IsSpawn && !shape)
	{
		return;
	}
	for(int i=0;i<3;i++)
	{
		Child[i] = NewObject<UStaticMeshComponent>(this, UStaticMeshComponent::StaticClass());
		Child[i]->RegisterComponentWithWorld(GetWorld());
		Child[i]->SetStaticMesh(shape);
		float rad = (2*PI) / 3;
		rad *= i;
		FVector loc = FVector(FMath::Cos(rad),FMath::Sin(rad), 0) * 100.0f;
		Child[i]->SetRelativeLocation(loc);
		Child[i]->AttachToComponent(this->RootComponent,FAttachmentTransformRules::KeepRelativeTransform);
	}
	IsSpawn = true;
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ARotatingActor::Counting, 1.0f, true);
}

void ARotatingActor::Counting()
{
	CountdownTimer--;
	if(CountdownTimer<0)
	{
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
	}
	for(int i = 0; i < 3; i++)
	{
		//Child[i]->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
		Child[i]->DestroyComponent();
	}
}
