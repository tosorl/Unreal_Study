// Fill out your copyright notice in the Description page of Project Settings.


#include "ColidingPawn.h"
#include "RotatingActor.h"

// Sets default values
AColidingPawn::AColidingPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ��Ʈ ������Ʈ�� ������ �����ϴ� ��ü�� �˴ϴ�
	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = SphereComponent;
	SphereComponent->InitSphereRadius(40.0f);
	SphereComponent->SetCollisionProfileName(TEXT("Pawn"));

	// ��ü�� ������� Ȯ���� �� �ֵ��� �޽� ������Ʈ ���� �� ��ġ ����
	UStaticMeshComponent* SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	SphereVisual->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	if (SphereVisualAsset.Succeeded())
	{
		SphereVisual->SetStaticMesh(SphereVisualAsset.Object);
		SphereVisual->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f));
		SphereVisual->SetWorldScale3D(FVector(0.8f));
	}

	// Ȱ��ȭ �Ǵ� ��Ȱ��ȭ��ų �� �ִ� ��ƼŬ �ý��� ����
	OurParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MovementParticles"));
	OurParticleSystem->SetupAttachment(SphereVisual);
	OurParticleSystem->bAutoActivate = false;
	OurParticleSystem->SetRelativeLocation(FVector(-20.0f, 0.0f, 20.0f));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Game/StarterContent/Particles/P_Fire.P_Fire"));
	if (ParticleAsset.Succeeded())
	{
		OurParticleSystem->SetTemplate(ParticleAsset.Object);
	}

	// ������ ���� ����Ͽ� ī�޶� �ε巴�� �ڿ������� ����� �����մϴ�.
	USpringArmComponent* SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
	SpringArm->SetupAttachment(RootComponent);
	//SpringArm->RelativeRotation = FRotator(-45.f, 0.f, 0.f);
	SpringArm->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 3.0f;

	// ī�޶� ����� ������ �Ͽ� ���Դϴ�.
	UCameraComponent* Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("ActualCamera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	// �⺻ �÷��̾� ��Ʈ�� ȹ��
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// �����Ʈ ������Ʈ �ν��Ͻ��� �����ϰ�, ��Ʈ�� ������Ʈ�϶� �̸��ϴ�.
	OurMovementComponent = CreateDefaultSubobject<UCollidingPawnMovementComponent>(TEXT("CustomMovementComponent"));
	OurMovementComponent->UpdatedComponent = RootComponent;
}

// Called when the game starts or when spawned
void AColidingPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AColidingPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AColidingPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("ParticleToggle", IE_Pressed, this, &AColidingPawn::ParticleToggle);

	InputComponent->BindAxis("MoveX", this, &AColidingPawn::MoveForward);
	InputComponent->BindAxis("MoveY", this, &AColidingPawn::MoveRight);
	InputComponent->BindAxis("Turn", this, &AColidingPawn::Turn);

	InputComponent->BindAction("Spawn",IE_Pressed, this, &ARotatingActor::SpawnMesh);
}

// Ŀ���� �̵�������Ʈ�� �����
UPawnMovementComponent* AColidingPawn::GetMovementComponent() const
{
	return OurMovementComponent;
}

void AColidingPawn::MoveForward(float AxisValue)
{
	if (OurMovementComponent && (OurMovementComponent->UpdatedComponent == RootComponent))
	{
		OurMovementComponent->AddInputVector(GetActorForwardVector() * AxisValue);
	}
}

void AColidingPawn::MoveRight(float AxisValue)
{
	if (OurMovementComponent && (OurMovementComponent->UpdatedComponent == RootComponent))
	{
		OurMovementComponent->AddInputVector(GetActorRightVector() * AxisValue);
	}
}

void AColidingPawn::Turn(float AxisValue)
{
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += AxisValue;
	SetActorRotation(NewRotation);
}

void AColidingPawn::ParticleToggle()
{
	if (OurParticleSystem && OurParticleSystem->Template)
	{
		OurParticleSystem->ToggleActive();
	}
}