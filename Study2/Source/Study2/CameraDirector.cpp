// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraDirector.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACameraDirector::ACameraDirector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    index=0;
}

// Called when the game starts or when spawned
void ACameraDirector::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACameraDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    //const float TimeBetweenCameraChanges = 4.0f;
    const float SmoothBlendTime = 0.75f;
    TimeToNextCameraChange -= DeltaTime;
    if (TimeToNextCameraChange <= 0.0f)
    {
        // ���� �÷��̾��� ��Ʈ���� ó���ϴ� ���͸� ã���ϴ�.
        APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
        if (OurPlayerController)
        {
            if (CamArr[index].Cam != nullptr) {
                OurPlayerController->SetViewTargetWithBlend(CamArr[index].Cam, SmoothBlendTime);
            }
            TimeToNextCameraChange += CamArr[index].view_time;
            index++;
            index %= CamArr.Num();
            /*if ((OurPlayerController->GetViewTarget() != CameraOne) && (CameraOne != nullptr))
            {
                // 1 �� ī�޶�� ��� ���� ���ϴ�.
                OurPlayerController->SetViewTarget(CameraOne);
            }
            else if ((OurPlayerController->GetViewTarget() != CameraTwo) && (CameraTwo != nullptr))
            {
                // 2 �� ī�޶�� �ε巴�� ��ȯ�մϴ�.
                OurPlayerController->SetViewTargetWithBlend(CameraTwo, SmoothBlendTime);
            }*/
        }
    }
}

