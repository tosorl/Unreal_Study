// Fill out your copyright notice in the Description page of Project Settings.


#include "UnrealCPPHUD.h"

AUnrealCPPHUD::AUnrealCPPHUD()
{
    // Set the crosshair texture
    static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshairTexObj(TEXT("/Game/Texture/Crosshair"));
    CrosshairTex = CrosshairTexObj.Object;

    static ConstructorHelpers::FClassFinder<UUserWidget> HealthBarObj(TEXT("/Game/Widget/HUD"));
    HUDWidgetClass = HealthBarObj.Class;
}

void AUnrealCPPHUD::DrawHUD()
{
    Super::DrawHUD();

    // Draw very simple crosshair

    // find center of the Canvas
    const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

    // offset by half the texture's dimensions so that the center of the texture aligns with the center of the Canvas
    const FVector2D CrosshairDrawPosition( (Center.X),
                                           (Center.Y + 20.0f));

    // draw the crosshair
    FCanvasTileItem TileItem( CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
    TileItem.BlendMode = SE_BLEND_Translucent;
    Canvas->DrawItem( TileItem );
}

void AUnrealCPPHUD::BeginPlay()
{
    Super::BeginPlay();

    if (HUDWidgetClass != nullptr)
    {
        CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);

        if (CurrentWidget)
        {
            CurrentWidget->AddToViewport();
        }
    }
}