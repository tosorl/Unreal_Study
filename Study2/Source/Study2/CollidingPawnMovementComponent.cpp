// Fill out your copyright notice in the Description page of Project Settings.


#include "CollidingPawnMovementComponent.h"

//Actor의 Tick함수와 비슷한 것, 각 프레임에 어떻게 이동할지 정함.
void UCollidingPawnMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // 모든 것이 아직 유효한지, 이동 가능한지 확인합니다.
    if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
    {
        return;
    }

    // ACollidingPawn::Tick 에 설정한 무브먼트 벡터를 구(한 뒤 소거)합니다.
    // ConsumeInputVector : 미동 입력을 저장하는 데 사용할 내장 변수 값을 보고 및 소거
    FVector DesiredMovementThisFrame = ConsumeInputVector().GetClampedToMaxSize(1.0f) * DeltaTime * 150.0f;
    if (!DesiredMovementThisFrame.IsNearlyZero())
    {
        FHitResult Hit;
        // SafeMoveUpdatedComponent : 언리얼 엔진 피직스를 사용하여 입체 장애물을 피해 Pawn Movement Component 를 이동
        SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);

        // 무언가에 부딛혔으면, 돌아가 봅니다.
        if (Hit.IsValidBlockingHit())
        {
            // SlideAlongSurface : 이동하다가 충돌 발생시 그냥 제자리에 멈춰 벽이나 경사로에 "달라붙기" 보다는,
            // 그 표면을 타고 부드럽게 미끄러지도록 하는 데 관련된 물리 계산 처리
            SlideAlongSurface(DesiredMovementThisFrame, 1.f - Hit.Time, Hit.Normal, Hit);
        }
    }
}