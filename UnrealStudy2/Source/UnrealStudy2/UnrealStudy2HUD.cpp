// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealStudy2HUD.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "TextureResource.h"
#include "CanvasItem.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"

AUnrealStudy2HUD::AUnrealStudy2HUD()
{
	// Set the crosshair texture
	static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshairTexObj(TEXT("/Game/FirstPerson/Textures/FirstPersonCrosshair"));
	CrosshairTex = CrosshairTexObj.Object;

	//UI 가져오기
	static ConstructorHelpers::FClassFinder<UUserWidget>AmmoTxt(TEXT("/Game/UI/fpsUI"));
	HUDWidgetClass = AmmoTxt.Class;
}


void AUnrealStudy2HUD::DrawHUD()
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

void AUnrealStudy2HUD::BeginPlay()
{
	Super::BeginPlay();
	if(HUDWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(),HUDWidgetClass);
		if(CurrentWidget)
		{
			CurrentWidget->AddToViewport();
		}
	}
}
