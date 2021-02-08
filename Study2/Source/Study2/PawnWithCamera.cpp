// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnWithCamera.h"

// Sets default values
APawnWithCamera::APawnWithCamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//������Ʈ�� �����մϴ�
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	OurCameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	OurCameraSpringArm->SetupAttachment(RootComponent);
	OurCameraSpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-60.0f, 0.0f, 0.0f));
	OurCameraSpringArm->TargetArmLength = 400.f;
	OurCameraSpringArm->bEnableCameraLag = true;
	OurCameraSpringArm->CameraLagSpeed = 3.0f;

	//spring arm �� ���Ͽ� ī�޶� ����
	OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));
	OurCamera->SetupAttachment(OurCameraSpringArm, USpringArmComponent::SocketName);

	//�⺻ �÷��̾��� ������� ȹ���մϴ�
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void APawnWithCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APawnWithCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//ZoomIn ��ư�� �������� ����, �ƴϸ� ���� �ܾƿ� ��ŵ�ϴ�
	if (bZoomingIn)
	{
		ZoomFactor += DeltaTime / 0.5f;         //0.5 �ʿ� ���� ����
	}
	else
	{
		ZoomFactor -= DeltaTime / 0.25f;        //0.25 �ʿ� ���� �ܾƿ�
	}
	ZoomFactor = FMath::Clamp<float>(ZoomFactor, 0.0f, 1.0f);
	//ZoomFactor �� ���� ������ ���� ���̿� ī�޶��� �þ� ����
	OurCamera->FieldOfView = FMath::Lerp<float>(90.0f, 60.0f, ZoomFactor);
	OurCameraSpringArm->TargetArmLength = FMath::Lerp<float>(400.0f, 300.0f, ZoomFactor);

	//������ Yaw�� ȸ��, �پ��ִ� ī�޶� ���� ȸ���˴ϴ�
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += CameraInput.X;
	SetActorRotation(NewRotation);

	//ī�޶��� Pitch�� ȸ��������, �׻� �Ʒ��� ������ ���ѽ�ŵ�ϴ�
	FRotator NewRotation1 = OurCameraSpringArm->GetComponentRotation();
	NewRotation1.Pitch = FMath::Clamp(NewRotation1.Pitch + CameraInput.Y, -80.0f, -15.0f);
	OurCameraSpringArm->SetWorldRotation(NewRotation1);

	//"MoveX" �� "MoveY" �࿡ ���� �̵��� ó���մϴ�
	if (!MovementInput.IsZero())
	{
		float addV = DeltaTime;
		if(Is_Running)
			addV *= 2.0f;
		//�̵� �Է� �� ���� �ʴ� 100 ���� �������� �����մϴ�
		MovementInput = MovementInput.GetSafeNormal() * 100.0f;
		FVector NewLocation = GetActorLocation();
		NewLocation += GetActorForwardVector() * MovementInput.X * addV;
		NewLocation += GetActorRightVector() * MovementInput.Y * addV;
		SetActorLocation(NewLocation);
	}
}

// Called to bind functionality to input
void APawnWithCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("Running",IE_Pressed,this,&APawnWithCamera::IsRunning);
	InputComponent->BindAction("Running",IE_Released,this,&APawnWithCamera::IsntRunning);
	
	//"ZoomIn" �� ���� �̺�Ʈ�� �ɾ��ݴϴ�
	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &APawnWithCamera::ZoomIn);
	InputComponent->BindAction("ZoomIn", IE_Released, this, &APawnWithCamera::ZoomOut);

	//�� �࿡ ���� �� ������ ó���� �ɾ��ݴϴ�
	InputComponent->BindAxis("MoveX", this, &APawnWithCamera::MoveForward);
	InputComponent->BindAxis("MoveY", this, &APawnWithCamera::MoveRight);
	InputComponent->BindAxis("CameraPitch", this, &APawnWithCamera::PitchCamera);
	InputComponent->BindAxis("Turn", this, &APawnWithCamera::YawCamera);
}

//�Է� �Լ�
void APawnWithCamera::MoveForward(float AxisValue)
{
	MovementInput.X = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}

void APawnWithCamera::MoveRight(float AxisValue)
{
	MovementInput.Y = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}

void APawnWithCamera::PitchCamera(float AxisValue)
{
	CameraInput.Y = AxisValue;
}

void APawnWithCamera::YawCamera(float AxisValue)
{
	CameraInput.X = AxisValue;
}

void APawnWithCamera::ZoomIn()
{
	bZoomingIn = true;
}

void APawnWithCamera::ZoomOut()
{
	bZoomingIn = false;
}

void APawnWithCamera::IsRunning()
{
	Is_Running = true;
}

void APawnWithCamera::IsntRunning()
{
	Is_Running = false;
}
