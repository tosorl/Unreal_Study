// Fill out your copyright notice in the Description page of Project Settings.


#include "DronePawn.h"

#include "DrawDebugHelpers.h"

// Sets default values
ADronePawn::ADronePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// 루트 컴포넌트는 물리에 반응하는 구체가 됩니다
	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	//SphereComponent->SetupAttachment(RootComponent);
	RootComponent = SphereComponent;
	SphereComponent->InitSphereRadius(40.0f);
	SphereComponent->SetCollisionProfileName(TEXT("Pawn"));

	// 구체가 어딨는지 확인할 수 있도록 메시 컴포넌트 생성 및 위치 조정
	UStaticMeshComponent* SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	SphereVisual->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	if (SphereVisualAsset.Succeeded())
	{
		SphereVisual->SetStaticMesh(SphereVisualAsset.Object);
		SphereVisual->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f));
		SphereVisual->SetWorldScale3D(FVector(0.8f));
		//SphereVisual->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	
	//컴포넌트를 생성합니다
	//RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	OurCameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	OurCameraSpringArm->SetupAttachment(RootComponent);
	OurCameraSpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-60.0f, 0.0f, 0.0f));
	OurCameraSpringArm->TargetArmLength = 400.f;
	OurCameraSpringArm->bEnableCameraLag = true;
	OurCameraSpringArm->CameraLagSpeed = 3.0f;

	//spring arm 끝 소켓에 카메라를 생성
	OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));
	OurCamera->SetupAttachment(OurCameraSpringArm, USpringArmComponent::SocketName);

	//기본 플레이어의 제어권을 획득합니다
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	//블루프린트 인스턴스 저장
	static ConstructorHelpers::FObjectFinder<UBlueprint> ItemBP(TEXT("/Game/BP_PingActor.BP_PingActor"));
	if(ItemBP.Object)
	{
		Ping_BP = Cast<UClass>(ItemBP.Object->GeneratedClass);
	}
}

// Called when the game starts or when spawned
void ADronePawn::BeginPlay()
{
	Super::BeginPlay();
	FullHealth = 1000.0f;
	Health = FullHealth;
	HealthPercentage = 1.0f;
	PrevHealth = HealthPercentage;
	DMG_dot = 100.0f;
}

// Called every frame
void ADronePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//ZoomIn 버튼이 눌렸으면 줌인, 아니면 도로 줌아웃 시킵니다
	/*if (bZoomingIn)
	{
		ZoomFactor += DeltaTime / 0.5f;         //0.5 초에 걸쳐 줌인
	}
	else
	{
		ZoomFactor -= DeltaTime / 0.25f;        //0.25 초에 걸쳐 줌아웃
	}
	ZoomFactor = FMath::Clamp<float>(ZoomFactor, 0.0f, 1.0f);
	//ZoomFactor 에 따라 스프링 암의 길이와 카메라의 시야 블렌딩
	OurCamera->FieldOfView = FMath::Lerp<float>(90.0f, 60.0f, ZoomFactor);
	OurCameraSpringArm->TargetArmLength = FMath::Lerp<float>(400.0f, 300.0f, ZoomFactor);*/

	//액터의 Yaw를 회전, 붙어있는 카메라도 따라서 회전됩니다
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += CameraInput.X;
	SetActorRotation(NewRotation);

	//카메라의 Pitch를 회전하지만, 항상 아래를 보도록 제한시킵니다
	FRotator NewRotation1 = OurCameraSpringArm->GetComponentRotation();
	NewRotation1.Pitch = FMath::Clamp(NewRotation1.Pitch + CameraInput.Y, -80.0f, -15.0f);
	OurCameraSpringArm->SetWorldRotation(NewRotation1);

	if(DroneActive)
	{
		//"MoveX" 와 "MoveY" 축에 따라 이동을 처리합니다
		if (!MovementInput.IsZero())
		{
			float addV = DeltaTime;
			if(Is_Running)
				addV *= 2.0f;
			//이동 입력 축 값에 초당 200 유닛 스케일을 적용합니다
			MovementInput = MovementInput.GetSafeNormal() * 200.0f;
			FVector NewLocation = GetActorLocation();
			NewLocation += GetActorForwardVector() * MovementInput.X * addV;
			NewLocation += GetActorRightVector() * MovementInput.Y * addV;
			SetActorLocation(NewLocation);
		}
		UpdateHealth(-1.0f * DMG_dot * DeltaTime);
			
	}
	else
	{
		UpdateHealth(DMG_dot * DeltaTime);
	}
}

// Called to bind functionality to input
void ADronePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAction("Running",IE_Pressed,this,&ADronePawn::IsRunning);
	InputComponent->BindAction("Running",IE_Released,this,&ADronePawn::IsntRunning);
	
	//"ZoomIn" 에 대한 이벤트를 걸어줍니다
	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &ADronePawn::ZoomIn);
	InputComponent->BindAction("ZoomIn", IE_Released, this, &ADronePawn::ZoomOut);

	//Raycasting 이벤트
	InputComponent->BindAction("SignalPing",IE_Pressed,this,&ADronePawn::PerformRaycast);
	
	//네 축에 대한 매 프레임 처리를 걸어줍니다
	InputComponent->BindAxis("MoveX", this, &ADronePawn::MoveForward);
	InputComponent->BindAxis("MoveY", this, &ADronePawn::MoveRight);
	InputComponent->BindAxis("CameraPitch", this, &ADronePawn::PitchCamera);
	InputComponent->BindAxis("Turn", this, &ADronePawn::YawCamera);

	InputComponent->BindAction("Grow",IE_Pressed,this,&ADronePawn::Active_trig);
	
}

//입력 함수
void ADronePawn::MoveForward(float AxisValue)
{
	MovementInput.X = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}

void ADronePawn::MoveRight(float AxisValue)
{
	MovementInput.Y = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}

void ADronePawn::PitchCamera(float AxisValue)
{
	CameraInput.Y = AxisValue;
}

void ADronePawn::YawCamera(float AxisValue)
{
	CameraInput.X = AxisValue;
}

void ADronePawn::ZoomIn()
{
	bZoomingIn = true;
}

void ADronePawn::ZoomOut()
{
	bZoomingIn = false;
}
void ADronePawn::IsRunning()
{
	Is_Running = true;
}

void ADronePawn::IsntRunning()
{
	Is_Running = false;
}

void ADronePawn::Active_trig()
{
	if(DroneActive)
	{
		GetWorld()->GetFirstPlayerController()->GetPawn()->SetActorLocation(Target_Person->GetActorLocation());
		OurCameraSpringArm->TargetArmLength = 400.0f;
	}
	else
	{
		FVector Active_loc = Target_Person->GetActorLocation() + FVector(0,0,Flight_Height);
		GetWorld()->GetFirstPlayerController()->GetPawn()->SetActorLocation(Active_loc);
		OurCameraSpringArm->TargetArmLength = -67.0f;
	}
	DroneActive = !DroneActive;
}

void ADronePawn::PerformRaycast()
{
	FHitResult* HitResult = new FHitResult();
	FVector StartTrace = OurCamera->GetComponentLocation();
	FVector ForwardVector = OurCamera->GetForwardVector();
	//StartTrace += (ForwardVector * 20.0f);
	FVector EndTrace = ((ForwardVector * 4000.f) + StartTrace);
	FCollisionQueryParams* TraceParam = new FCollisionQueryParams();

	UWorld* ThisWorld = GetWorld();
	if(ThisWorld)
	{
		if(ThisWorld->LineTraceSingleByChannel(*HitResult,StartTrace,EndTrace,ECC_Visibility,*TraceParam))
		{
			//DrawDebugLine(GetWorld(),StartTrace,EndTrace,FColor(255, 0, 0), true);
			GEngine->AddOnScreenDebugMessage(-1, 5.f,FColor::Red,FString::Printf(TEXT("You hit: %s"),*HitResult->Actor->GetName()));
			GEngine->AddOnScreenDebugMessage(-1, 5.f,FColor::Red,FString::Printf(TEXT("location X: %f, Y: %f, Z: %f"),
                                                                                                            HitResult->Location.X,
                                                                                                            HitResult->Location.X,
                                                                                                            HitResult->Location.X));
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = nullptr;
			SpawnParams.Instigator = GetInstigator();
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			
			ThisWorld->SpawnActor<AActor>(Ping_BP,HitResult->Location + FVector(0.0f, 0.0f, 50.0f),FRotator::ZeroRotator,SpawnParams);
        }
	}
	
}


float ADronePawn::GetHealth()
{
	return HealthPercentage;
}

void ADronePawn::UpdateHealth(float HealthChange)
{
	Health += HealthChange;
	Health = FMath::Clamp(Health, 0.0f, FullHealth);
	if(Health<=0.0f)
		Active_trig();
	
	PrevHealth = HealthPercentage;
	HealthPercentage = Health/FullHealth;
}
