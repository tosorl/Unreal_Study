// Fill out your copyright notice in the Description page of Project Settings.


#include "Countdown.h"

// Sets default values
ACountdown::ACountdown()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	CountdownText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("CountdownNumber"));
	CountdownText->SetHorizontalAlignment(EHTA_Center);
	CountdownText->SetWorldSize(150.0f);
	RootComponent = CountdownText;
	CountdownTime = 3;
	burningtime = 3;
	
	// Ȱ��ȭ �Ǵ� ��Ȱ��ȭ��ų �� �ִ� ��ƼŬ �ý��� ����
	OurParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MovementParticles"));
	OurParticleSystem->SetupAttachment(RootComponent);
	OurParticleSystem->bAutoActivate = false;
	OurParticleSystem->SetRelativeLocation(FVector(-20.0f, 0.0f, 20.0f));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Game/StarterContent/Particles/P_Fire.P_Fire"));
	if (ParticleAsset.Succeeded())
	{
		OurParticleSystem->SetTemplate(ParticleAsset.Object);
	}
	
}

// Called when the game starts or when spawned
void ACountdown::BeginPlay()
{
	Super::BeginPlay();
	//�����ڰ� �ƴ� BeginPlay�� �ؽ�Ʈǥ�ø� �ʱ�ȭ �ϴ� ����:
	//�𸮾� �����Ϳ��� ������ ������ ���� ������ ����, BeginPlay������ �Ҵ�Ǳ� �����̴�.
	UpdateTimerDisplay();
	GetWorldTimerManager().PauseTimer(FuelTimer);
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ACountdown::AdvanceTimer, 1.0f, true);
	AddFuel();
}

// Called every frame
/*void ACountdown::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}*/

void ACountdown::UpdateTimerDisplay() {
	CountdownText->SetText(FText::AsNumber(FMath::Max(CountdownTime, 0)));
}

void ACountdown::AdvanceTimer() {
	--CountdownTime;
	UpdateTimerDisplay();
	if (CountdownTime < 1) {
		CountdownTime = 2;
		FRotator tmp = GetActorRotation();
		SetActorRotation(target);
		target = tmp;
		GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ACountdown::AdvanceTimer2, 1.0f, true);
		//ī��Ʈ �ٿ��� �Ϸ�Ǿ�����, Ÿ�̸Ӹ� ������ŵ�ϴ�.
		//GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
		if (OurParticleSystem && OurParticleSystem->Template)
		{
			OurParticleSystem->ToggleActive();
		}
		CountdownHasFinished();
	}
}

void ACountdown::AdvanceTimer2() {
	--CountdownTime;
	//UE_LOG(LogTemp, Log, "check");
	if (CountdownTime < 1) {
		SetActorRotation(target);
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
		if (OurParticleSystem && OurParticleSystem->Template)
		{
			OurParticleSystem->ToggleActive();
		}
	}
}

void ACountdown::CountdownHasFinished_Implementation() {
	//Ư�������� ��ȯ�մϴ�
	CountdownText->SetText(FText::FromString(TEXT("Fire!")));
}

void ACountdown::burning() {
	burningtime--;
	if (burningtime < 1) {
		GetWorldTimerManager().ClearTimer(FuelTimer);
		GetWorldTimerManager().PauseTimer(FuelTimer);
	}
}

void ACountdown::AddFuel_Implementation() {
	if (!GetWorldTimerManager().IsTimerActive(FuelTimer)) {
		GetWorldTimerManager().UnPauseTimer(FuelTimer);
		GetWorldTimerManager().SetTimer(FuelTimer, this, &ACountdown::burning, 1.0f, true);
	}
	
}

void ACountdown::DouseWithWater() {
	if(GetWorldTimerManager().IsTimerActive(FuelTimer))
		GetWorldTimerManager().PauseTimer(FuelTimer);
}