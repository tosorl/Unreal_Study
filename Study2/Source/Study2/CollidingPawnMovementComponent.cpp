// Fill out your copyright notice in the Description page of Project Settings.


#include "CollidingPawnMovementComponent.h"

//Actor�� Tick�Լ��� ����� ��, �� �����ӿ� ��� �̵����� ����.
void UCollidingPawnMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // ��� ���� ���� ��ȿ����, �̵� �������� Ȯ���մϴ�.
    if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
    {
        return;
    }

    // ACollidingPawn::Tick �� ������ �����Ʈ ���͸� ��(�� �� �Ұ�)�մϴ�.
    // ConsumeInputVector : �̵� �Է��� �����ϴ� �� ����� ���� ���� ���� ���� �� �Ұ�
    FVector DesiredMovementThisFrame = ConsumeInputVector().GetClampedToMaxSize(1.0f) * DeltaTime * 150.0f;
    if (!DesiredMovementThisFrame.IsNearlyZero())
    {
        FHitResult Hit;
        // SafeMoveUpdatedComponent : �𸮾� ���� �������� ����Ͽ� ��ü ��ֹ��� ���� Pawn Movement Component �� �̵�
        SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);

        // ���𰡿� �ε�������, ���ư� ���ϴ�.
        if (Hit.IsValidBlockingHit())
        {
            // SlideAlongSurface : �̵��ϴٰ� �浹 �߻��� �׳� ���ڸ��� ���� ���̳� ���ο� "�޶�ٱ�" ���ٴ�,
            // �� ǥ���� Ÿ�� �ε巴�� �̲��������� �ϴ� �� ���õ� ���� ��� ó��
            SlideAlongSurface(DesiredMovementThisFrame, 1.f - Hit.Time, Hit.Normal, Hit);
        }
    }
}