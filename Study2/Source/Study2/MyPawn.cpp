// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// 무언가를 붙일 더미 루트 컴포넌트를 만듭니다
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	// 카메라와 보이는 오브젝트를 만듭니다
	UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	// 루트 컴포넌트에 카메라와 보이는 오브젝트를 붙입니다. 카메라를 이격 및 회전시킵니다.
	OurCamera->SetupAttachment(RootComponent);
	OurCamera->SetRelativeLocation(FVector(-250.0f, 0.0f, 250.0f));
	OurCamera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	OurVisibleComponent->SetupAttachment(RootComponent);
	addV = 0;
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float CurrentScale = OurVisibleComponent->GetComponentScale().X;
	if (bGrowing) {
		if(!CurrentVelocity.IsZero())
		{
			CurrentScale *= 2.0f;
		}
		else
		{
			//1초에 걸쳐 2배로 키움
            CurrentScale += DeltaTime;
		}
		
	}
	else {
		//키운 속도대로 줄임
		CurrentScale -= (DeltaTime * 0.5f);
	}
	CurrentScale = FMath::Clamp(CurrentScale, 1.0f, 2.0f);
	OurVisibleComponent->SetWorldScale3D(FVector(CurrentScale));

	if (!CurrentVelocity.IsZero()) {
		addV += DeltaTime * 0.5f;
		FVector NewLocation = GetActorLocation() + (CurrentVelocity * addV);
		SetActorLocation(NewLocation);
	}
	else
	{
		addV = 0.0f;
	}
	addV = FMath::Clamp(addV,0.0f,1.0f);
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Grow 키 상호작용
	InputComponent->BindAction("Grow", IE_Pressed, this, &AMyPawn::StartGrowing);
	InputComponent->BindAction("Grow", IE_Released, this, &AMyPawn::StopGrowing);

	// Move_X , Move_Y 바인딩
	InputComponent->BindAxis("MoveX", this, &AMyPawn::Move_XAxis);
	InputComponent->BindAxis("MoveY", this, &AMyPawn::Move_YAxis);
}

void AMyPawn::Move_XAxis(float AxisValue) {
	// 초당 100유닛을 앞 또는 뒤로 움직인다.
	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void AMyPawn::Move_YAxis(float AxisValue) {
	// 초당 100유닛을 좌 또는 우로 움직인다.
	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void AMyPawn::StartGrowing() {
	bGrowing = true;
}

void AMyPawn::StopGrowing() {
	bGrowing = false;
}